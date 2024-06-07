from PIL import Image, ImageDraw, ImageFont

def add_numbers_to_chessboard(image_path, output_path, font_size=30):
    # Open the image
    img = Image.open(image_path)
    draw = ImageDraw.Draw(img)
    
    # Load a font with specified size
    try:
        font = ImageFont.truetype("arial.ttf", font_size)
    except IOError:
        font = ImageFont.load_default()

    # Get the size of the image
    width, height = img.size
    
    # Calculate the size of each square
    square_size = width // 8

    # Generate the numbers from 0 to 63 left to right
    numbers = list(range(0, 64))

    # Add numbers to the image
    for i, number in enumerate(numbers):
        x = (i % 8) * square_size
        y = (i // 8) * square_size
        text = str(number)
        bbox = draw.textbbox((0, 0), text, font=font)
        text_width = bbox[2] - bbox[0]
        text_height = bbox[3] - bbox[1]
        text_x = x + (square_size - text_width) / 2
        text_y = y + (square_size - text_height) / 2
        draw.text((text_x, text_y), text, fill="black", font=font)

    # Save the image
    img.save(output_path)

# Example usage
add_numbers_to_chessboard('board_brown_sand.png', 'numbered_chessboard.png', font_size=64)
