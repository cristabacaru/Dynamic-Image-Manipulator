# Image Processing Project

## Overview
This project implements a variety of image processing functionalities that allow users to dynamically manipulate images. The code is designed to load, save, and transform images using various operations such as cropping, rotating, flipping, extending, and applying filters. The project is created strictly using the fundamentals of C programming, making it a challenging endeavor that emphasizes core programming concepts and manual memory management.

## Functionalities
The program provides an interactive command-line interface that enables users to perform the following operations:

- **Load Images**: Dynamically allocate and load images from specified paths.
- **Save Images**: Save modified images back to disk.
- **Transform Images**: Apply operations such as flipping, rotating, cropping, and extending images.
- **Apply Filters**: Create and apply customizable filters to enhance or modify images.
- **Memory Management**: Efficiently manage memory allocation and deallocation for images and filters.

### Interactive Commands
Users can interact with the program through a set of commands, including:

| Command | Parameters                             | Description                                                                                          |
|---------|----------------------------------------|------------------------------------------------------------------------------------------------------|
| e       | -                                      | Exit - closes the program                                                                            |
| l       | N M path                               | Load - allocates and loads an image of size NxM from the specified path                             |
| s       | index path                             | Save - saves the image at the specified index to the specified path                                  |
| ah      | index                                  | Apply Horizontal Flip - applies a horizontal flip operation on the image at the specified index      |
| ar      | index                                  | Apply Rotate - applies a left rotation operation on the image at the specified index                 |
| ac      | index x y w h                         | Apply Crop - crops the image at the specified index with the given parameters                        |
| ae      | index rows cols R G B                 | Apply Extend - extends the image at the specified index with the given parameters                    |
| ap      | index_dst index_src x y               | Apply Paste - pastes the source image into the destination image at specified coordinates             |
| cf      | size [list of values]                 | Create filter - allocates and creates a filter of the specified size with the given values           |
| af      | index_img index_filter                 | Apply filter - applies the filter at the specified index to the image at the specified index_img     |
| df      | index_filter                           | Delete filter - deletes and deallocates the filter at the specified index_filter                     |
| di      | index_img                              | Delete image - deletes and deallocates the image at the specified index_img                         |

### Example of Functionality
Here’s an example of how to use the commands to manipulate images:

```plaintext
l 768 1024 ./cat.bmp   # Load an image "cat.bmp" with dimensions 768x1024
l 768 1024 ./dog.bmp   # Load another image "dog.bmp" with the same dimensions
ah 0                   # Apply a horizontal flip to the first image (index 0)
ac 1 300 300 200 100   # Crop the second image (index 1) starting from (300, 300) with width 200 and height 100
cf 3 0 1 0 1 1 1 0 1 0  # Create a filter of size 3 with specified values
af 1 0                 # Apply the filter from index 1 to the image at index 0
ap 0 1 300 300        # Paste the image from index 1 into index 0 at (300, 300)
s 0 ./output.bmp      # Save the modified first image as "output.bmp"
df 0                   # Delete the filter at index 0
di 0                   # Delete the image at index 0
di 0                   # Delete the image at index 0 (second call, after deletion, may be a mistake)
e                      # Exit the program
```
## Getting Started
To run the Image Processing Project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/cristabacaru/Dynamic-Image-Manipulator.git
