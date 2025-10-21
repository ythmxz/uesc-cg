import sys
import xml.etree.ElementTree as ET

def xml_to_txt(xml_path: str, txt_path: str) -> None:
    tree = ET.parse(xml_path)
    root = tree.getroot()

    # lista de tuplas (label, x, y)
    coords_list = []

    # Encontra todos os elementos do tipo "point"
    for element in root.findall(".//element[@type='point']"):
        label = element.get("label") or ""
        coords_tag = element.find("coords")

        if coords_tag is not None:
            x = coords_tag.get("x")
            y = coords_tag.get("y")

            if x is not None and y is not None:
                try:
                    xf = float(x)
                    yf = float(y)
                except ValueError:
                    continue
                coords_list.append((label, xf, yf))

    # Escreve no arquivo ".txt"
    with open(txt_path, "a", encoding="utf-8") as file:
        if len(sys.argv) > 1:
            file.write(f"\n{sys.argv[1]}:\n\n")
        else:
            file.write("\n\n")

        for label, x, y in coords_list:
            if label:
                file.write(f"{label}: ")
            file.write(f"glVertex2f(x + {(20.0 * x):.1f}, y + {(20.0 * y):.1f});\n")

    print(f"{len(coords_list)} coordenadas salvas em: {txt_path}")


def main() -> None:
    xml_to_txt("C:\\Users\\Yuri\\Downloads\\geogebra.xml", "02\\coordenadas.txt")


if __name__ == "__main__":
    main()
