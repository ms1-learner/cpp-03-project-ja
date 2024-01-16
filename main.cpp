#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>

#include <iostream>

Fl_JPEG_Image *originalImage;
Fl_Image *currentImage;
Fl_Box *imageBox;
double zoomFactor = 1.0;

void zoomIn(Fl_Widget*, void*) {
    zoomFactor *= 1.1;
    Fl_Image *scaled = originalImage->copy(originalImage->w() * zoomFactor, originalImage->h() * zoomFactor);
    imageBox->image(scaled);
    imageBox->parent()->redraw();
}

void zoomOut(Fl_Widget*, void*) {
    zoomFactor *= 0.9;
    Fl_Image *scaled = originalImage->copy(originalImage->w() * zoomFactor, originalImage->h() * zoomFactor);
    imageBox->image(scaled);
    imageBox->parent()->redraw();
}

Fl_Image* rotateImage(Fl_Image *img) {
    int w = img->w();
    int h = img->h();
    const uchar *in = (const uchar*)img->data()[0];

    uchar *out = new uchar[w * h * 3];
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int ni = (x * h + (h - y - 1)) * 3;
            int oi = (y * w + x) * 3;
            out[ni] = in[oi];         // R
            out[ni + 1] = in[oi + 1]; // G
            out[ni + 2] = in[oi + 2]; // B
        }
    }

    Fl_RGB_Image *rotated = new Fl_RGB_Image(out, h, w, 3);
    rotated->alloc_array = 1; // Tell FLTK to manage the memory
    return rotated;
}

void rotate(Fl_Widget*, void*) {
    Fl_Image *rotatedImage = rotateImage(currentImage);
    delete currentImage;
    currentImage = rotatedImage;
    imageBox->image(currentImage);
    imageBox->parent()->redraw();
}

int main() {
    originalImage = new Fl_JPEG_Image("car.jpg");
    if (!originalImage->data()) {
        printf("Failed to load image\n");
        return 1;
    }

    currentImage = originalImage->copy();

    int windowWidth = 800;
    int windowHeight = 600;
    Fl_Window *window = new Fl_Window(windowWidth, windowHeight, "FLTK Image Viewer");

    int boxWidth = 780;
    int boxHeight = 550;
    imageBox = new Fl_Box(10, 10, boxWidth, boxHeight);
    imageBox->image(currentImage);

    Fl_Button *zoomInButton = new Fl_Button(10, 570, 50, 30, "+");
    zoomInButton->callback(zoomIn);

    Fl_Button *zoomOutButton = new Fl_Button(70, 570, 50, 30, "-");
    zoomOutButton->callback(zoomOut);

    Fl_Button *rotateButton = new Fl_Button(130, 570, 50, 30, "rot");
    rotateButton->callback(rotate);

    window->end();
    window->show();
    return Fl::run();
}
