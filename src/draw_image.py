import sys
from PIL import Image

def overlay_images(png_path, x, y):
    # Abre o arquivo bmp
    with Image.open("../images/mapa_unisc.bmp") as bmp_img:
        # Abre o arquivo PNG
        with Image.open(png_path) as png_img:
            # PNG precisa ser RGBA para ter transparência
            if png_img.mode != 'RGBA':
                png_img = png_img.convert('RGBA')
            
            # Coloca o PNG em cima do BMP
            bmp_img.paste(png_img, (x, y), png_img)

            # Salva o arquivo
            bmp_img.save("../images/mapa_unisc.bmp", 'BMP')

# Usando argumentos da linha de comando
if len(sys.argv) < 3:
    print("Uso: python script.py <png_path> <x_pos> <y_pos>")
else:
    png_path = sys.argv[1]
    x_pos = int(sys.argv[2])
    y_pos = int(sys.argv[3])

    overlay_images(png_path, x_pos, y_pos)

