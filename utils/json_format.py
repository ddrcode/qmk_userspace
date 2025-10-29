#!/usr/bin/env python3
import argparse, json, sys, textwrap
from pathlib import Path

# Known layout -> row-counts mapping (add more as you need)
KNOWN_SHAPES = {
    "LAYOUT_ansi_89":  [16, 16, 16, 15, 15, 11],  # Keychron Q10 ANSI encoder
    "LAYOUT_ortho_5x15": [15, 15, 15, 15, 15],
}

def parse_args():
    p = argparse.ArgumentParser(
        description="Pretty-format a QMK keymap.json so each layer is shown in rows/columns.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    p.add_argument("input", type=Path, help="Path to keymap.json")
    p.add_argument("--shape", help="Row sizes, e.g. 16,16,16,15,15,11")
    p.add_argument("--in-place", action="store_true", dest="in_place", help="Overwrite the input file")
    p.add_argument("--output", type=Path, help="Write to this path instead of stdout")
    return p.parse_args()

def detect_shape(doc):
    # 1) explicit shape override
    # 2) infer from layout name if known
    layout = doc.get("layout") or doc.get("layout_alias")
    if layout in KNOWN_SHAPES:
        return KNOWN_SHAPES[layout], layout
    return None, layout

def fmt_layer_as_rows(layer, rowsizes, indent="      "):
    """Return a JSON-valid string for one layer with row breaks at rowsizes."""
    out = []
    pos = 0
    total = len(layer)
    for i, n in enumerate(rowsizes):
        if pos >= total: break
        row = layer[pos:pos+n]
        pos += n
        # Join row items with proper JSON quoting
        row_json = ", ".join(json.dumps(x) for x in row)
        # Put a trailing comma except for last row (we’ll be inside an array)
        comma = "," if pos < total else ("," if i < len(rowsizes)-1 else "")
        out.append(f"{indent}{row_json}{comma}")
    # If there are leftover items (shape shorter than data), append them on one line
    if pos < total:
        rest = ", ".join(json.dumps(x) for x in layer[pos:])
        out.append(f"{indent}{rest}")
    return "[\n" + "\n".join(out) + "\n    ]"

def main():
    args = parse_args()
    doc = json.loads(args.input.read_text())

    # Determine row sizes
    rowsizes = None
    layout_name = None
    if args.shape:
        try:
            rowsizes = [int(x) for x in args.shape.split(",") if x.strip()]
        except ValueError:
            sys.exit("Invalid --shape. Example: --shape 16,16,16,15,15,11")
    else:
        rowsizes, layout_name = detect_shape(doc)

    # If still unknown, try a best-effort guess from first layer length
    layers = doc.get("layers")
    if not isinstance(layers, list) or not layers:
        sys.exit("This JSON has no 'layers' array.")

    total_keys = len(layers[0]) if isinstance(layers[0], list) else 0
    if rowsizes is None:
        # naive heuristic for common layouts of 89 and 75 etc.
        guess_map = {
            89: [16,16,16,15,15,11],
            75: [15,15,15,15,15],  # fallback
        }
        rowsizes = guess_map.get(total_keys)
        if not rowsizes:
            sys.exit(
                "Could not detect row shape. Provide one with --shape, e.g. --shape 16,16,16,15,15,11"
            )

    expected = sum(rowsizes)
    # Validate layers length
    problems = []
    for i, layer in enumerate(layers):
        if len(layer) != expected:
            problems.append((i, len(layer)))
    if problems:
        msg = "\n".join(f"  - layer {i}: has {n} keys, expected {expected}" for i, n in problems)
        print(
            f"WARNING: layer length mismatch with shape {rowsizes} (sum={expected}):\n{msg}",
            file=sys.stderr,
        )

    # Build pretty JSON string manually to control row breaks inside arrays
    # Copy all fields except layers via json.dumps, then inject layers pretty
    doc_copy = dict(doc)
    layers_data = doc_copy.pop("layers")

    # Dump header without layers
    header = json.dumps(doc_copy, indent=2, ensure_ascii=False)
    # Insert "layers": [
    # We place it before the closing brace
    if header.endswith("}"):
        header = header[:-1]

    # Construct pretty layers
    pretty_layers_lines = []
    pretty_layers_lines.append('  ,\n  "layers": [')
    for idx, layer in enumerate(layers_data):
        pretty = fmt_layer_as_rows(layer, rowsizes)
        comma = "," if idx < len(layers_data) - 1 else ""
        pretty_layers_lines.append(f"    {pretty}{comma}")
    pretty_layers_lines.append("  ]\n}")

    pretty_json = header + "".join(pretty_layers_lines)

    # Output
    if args.in_place:
        args.input.write_text(pretty_json + "\n")
    elif args.output:
        args.output.write_text(pretty_json + "\n")
    else:
        sys.stdout.write(pretty_json + "\n")

if __name__ == "__main__":
    main()
