from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import inch
from reportlab.lib import colors
import os

# Get all .cpp files in the current directory
cpp_files = [f for f in os.listdir() if f.endswith(".cpp")]

# Create PDF
output_pdf = "combined_code.pdf"
c = canvas.Canvas(output_pdf, pagesize=A4)
width, height = A4

# Set font and text box style
c.setFont("Courier", 10)

# Define the box dimensions and margin
margin = inch
box_padding = 5
box_width = width - 2 * margin
box_height = height - 2 * margin
y_position = height - margin

# Set the text color to black
c.setFillColor(colors.black)

# Iterate over each .cpp file
for filename in cpp_files:
    with open(filename, "r") as f:
        code = f.read()

    code = code.replace("\r\n", "\n")  # Normalize line endings
    code = code.replace("\r", "\n")  # Normalize line endings
    code = code.replace("\t", "    ")  # Replace tabs with spaces
    code = "\n" + code

    # Add file name as a header
    c.setFont("Courier", 12)
    c.drawString(margin, y_position, f"{filename[:-4]}")
    y_position -= 20  # Move down for the code

    # Draw the box for code (only the border)
    c.setStrokeColor(colors.black)
    c.rect(margin, y_position - box_height, box_width, box_height)

    # Add code inside the box
    text_object = c.beginText(margin + box_padding, y_position - box_padding)
    text_object.setFont("Courier", 6)

    for line in code.splitlines():
        text_object.textLine(line)

    c.drawText(text_object)

    # Update y_position for the next file
    y_position -= box_height + 20

    # If we run out of space on the current page, create a new page
    if y_position < margin:
        c.showPage()
        c.setFont("Courier", 10)
        y_position = height - margin

# Save the PDF
c.save()

print(f"PDF generated: {output_pdf}")