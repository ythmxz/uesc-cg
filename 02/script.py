import sys
import xml.etree.ElementTree as ET

def xml_to_txt(xml_path: str, txt_path: str) -> None:
    tree = ET.parse(xml_path)
    root = tree.getroot()

    coords_list = []

    # Encontra todos os elementos do tipo "point"
    for element in root.findall(".//element[@type='point']"):
        coords_tag = element.find("coords")

        if coords_tag is not None:
            x = coords_tag.get("x")
            y = coords_tag.get("y")

            if x is not None and y is not None:
                coords_list.append((x, y))

    # Escreve no arquivo ".txt"
    with open(txt_path, "a", encoding="utf-8") as file:
        file.write(f"\n{sys.argv[1]}:\n\n") if len(sys.argv) > 1 else file.write("\n\n")

        for x, y in coords_list:
            file.write(f"glVertex2f(x + {(10.0 * float(x)):.1f}, y + {(10.0 * float(y)):.1f});\n")

    print(f"{len(coords_list)} coordenadas salvas em: {txt_path}")


def main() -> None:
    xml_to_txt("geogebra.xml", "coordenadas.txt")


if __name__ == "__main__":
    main()
