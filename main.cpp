#include "glm/matrix.hpp"
#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <complex>


void keep_green_only(sil::Image& image) 
{
    for (int x{0}; x<image.width(); x++){
        for (int y{0}; y<image.height(); y++){
            image.pixel(x,y).r=0.f;
            image.pixel(x,y).b=0.f;
        }
    }
}

void color_switch(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        std::swap(color.r,color.g);
    }
}

void black_and_white(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        float red = color.r;
        float green = color.g;
        float blue = color.b;
        float total = (red + green + blue)/3;
        color.r=total;
        color.g=total;
        color.b=total;
    }
}

void negatif(sil::Image& image){
    for(glm::vec3& color : image.pixels()){
        float nred = 1.0f-color.r;
        float ngreen = 1.0f-color.g;
        float nblue = 1.0f-color.b;
        color.r=nred;
        color.g=ngreen;
        color.b=nblue;
    }
}

void degrade(sil::Image& image){
    for (int x{0}; x<image.width(); x++){
        for (int y{0}; y<image.height(); y++){
            image.pixel(x, y) = glm::vec3{float(x) / float(image.width() - 1)};
        }
    }
}

void mirror(sil::Image& image){
    for (int x{0}; x<image.width()/2; x++){
        for (int y{0}; y<image.height(); y++){
            int opposé = image.width() - 1 - x;
            std::swap(image.pixel(x, y),image.pixel(opposé,y));
        }
    }
}

void noise(sil::Image& image){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y).r+= random_float(-0.2f, 0.2f);
            image.pixel(x, y).g+= random_float(-0.2f, 0.2f);
            image.pixel(x, y).b+= random_float(-0.2f, 0.2f);
        }
    }
} 


void rotation(sil::Image& image){
    int new_width = image.height();
    int new_height = image.width();
    sil::Image new_image{new_width, new_height};
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y<image.height(); y++){
            int new_x = image.height() - 1 - y;
            int new_y = x;
            new_image.pixel(new_x, new_y)=image.pixel(x, y);
        }
    }
    image = new_image;
}

void rgb_split(sil::Image& image){
    sil::Image new_image{image.width(), image.height()};
    int decalage = 25;

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if (x + decalage < image.width()){
                new_image.pixel(x, y).r = image.pixel(x + decalage, y).r;
            }
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            if (x - decalage >= 0){
                new_image.pixel(x, y).b = image.pixel(x - decalage, y).b;
            }
        }
    }
    image = new_image;
}

void luminosite(sil::Image& image, float exposant){
    for (glm::vec3& color : image.pixels()){
        color.r = std::pow(color.r, exposant);
        color.g = std::pow(color.g, exposant);
        color.b = std::pow(color.b, exposant);
    }
}

void disque(sil::Image& image, int radius){
    int centre_x = image.width() / 2;
    int centre_y = image.height() / 2;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int dx = x - centre_x;
            int dy = y - centre_y;
            if (dx * dx + dy * dy <= radius * radius){
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void cercle(sil::Image& image,int centre_x,int centre_y, int radius, int epaisseur){
    centre_x = image.width() / 2;
    centre_y = image.height() / 2;
    int inter = radius - epaisseur;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int dx = x - centre_x;
            int dy = y - centre_y;
            int dist = dx * dx + dy * dy;
            if (dist <= radius * radius && dist >= inter * inter){
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

void cercle2(sil::Image& image,int centre_x,int centre_y, int radius, int epaisseur){
    int inter = radius - epaisseur;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int dx = x - centre_x;
            int dy = y - centre_y;
            int dist = dx * dx + dy * dy;
            if (dist <= radius * radius && dist >= inter * inter){
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}



void disque2(sil::Image& image, int centre_x, int centre_y, int radius){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int dx = x - centre_x;
            int dy = y - centre_y;
            if (dx * dx + dy * dy <= radius * radius){
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}


void rosace(sil::Image& image, int radius, int epaisseur){
    int centre_x = image.width() / 2;
    int centre_y = image.height() / 2;
    int nb_cercles = 6;
    float pi = 3.14159265f;
    cercle2(image, centre_x, centre_y, radius, epaisseur);
    for (int i{0}; i < nb_cercles; i++){
        float angle = i * (2.f * pi / nb_cercles);
        int cx = centre_x + std::cos(angle) * radius;
        int cy = centre_y + std::sin(angle) * radius;
        cercle2(image, cx, cy, radius,epaisseur);
    }
}


void mosaique(sil::Image& image, int repetition){
    int new_width = image.width() * repetition;
    int new_height = image.height() * repetition;
    sil::Image new_image{new_width, new_height};
    for (int x{0}; x < new_width/2; x++){
        for (int y{0}; y < new_height; y++){
            new_image.pixel(x, y) = image.pixel(x% image.width(), y% image.height());
            int opposé = image.width()-1 - x;
            std::swap(image.pixel(x, y),image.pixel(opposé,y));
        }
    }
    image = new_image;
}


void mosaique_miroir(sil::Image& image, int repetition){
    int new_width = image.width() * repetition;
    int new_height = image.height() * repetition;
    sil::Image new_image{new_width, new_height};
    for (int x{0}; x < new_width; x++){
        for (int y{0}; y < new_height; y++){
            int rep_x = x / image.width();     
            int rep_y = y / image.height();
            int pix_x = x% image.width();
            int pix_y = y% image.height();
            if (rep_x % 2 == 1){
                pix_x = image.width() - 1 - pix_x;}
            if (rep_y % 2 == 1){
                pix_y = image.height() - 1 - pix_y;}
            new_image.pixel(x,y) = image.pixel(pix_x, pix_y);
        }
    }
    image = new_image;
}

void glitch(sil::Image& image){
    int nb_iterations = 50;
    for (int i{0}; i < nb_iterations; i++){
        int rect_width = random_int(10, 80);
        int rect_height = random_int(5, 10);
        int x1 = random_int(0, image.width() - rect_width);
        int y1 = random_int(0, image.height() - rect_height);
        int x2 = random_int(0, image.width() - rect_width);
        int y2 = random_int(0, image.height() - rect_height);
        for (int x{0}; x < rect_width; x++){
            for (int y{0}; y< rect_height; y++){
                std::swap(image.pixel(x1 + x, y1+y), image.pixel(x2 + x, y2 + y));
            }
        }
    }
}

float luminosite_pixel(glm::vec3 color){
    float red = color.r;
    float green= color.g;
    float blue = color.b;
    float total = (red + green+blue)/3;
    return total;
}


void tri(sil::Image& image){
    std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const& color1, glm::vec3 const& color2){
        return luminosite_pixel(color1)< luminosite_pixel(color2);
    });
}


void tri_lignes(sil::Image& image){
    for (int y{0}; y < image.height(); y++){
        int debut = y * image.width();
        int fin = (y+1) * image.width();
        std::sort(image.pixels().begin() + debut, image.pixels().begin() + fin, [](glm::vec3 const& color1, glm::vec3 const& color2){
            return luminosite_pixel(color1) < luminosite_pixel(color2);
        });
    }
}


void tri_random(sil::Image& image){
    int nb_iterations = 500;
    for (int i{0}; i < nb_iterations; i++){
        int longueur = random_int(10, 100);
        int debut = random_int(0, image.pixels().size()- longueur);
        std::sort(image.pixels().begin() + debut, image.pixels().begin() + debut+ longueur, [](glm::vec3 const& color1, glm::vec3 const& color2){
            return luminosite_pixel(color1) < luminosite_pixel(color2);
        });
    }
}

void mandelbrot(sil::Image& image){
    int max_iterations = 100;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            float cx = (float(x) / float(image.width())) * 4.f - 2.f;
            float cy = (float(y) / float(image.height())) * 4.f- 2.f;
            std::complex<float> c{cx, cy};
            std::complex<float> z{0.f, 0.f};
            int nb_iter = 0;
            while (nb_iter < max_iterations && std::abs(z) <= 2.f){
                z = z * z + c;
                nb_iter++;}
            float gris = float(nb_iter) / float(max_iterations);
            image.pixel(x, y) = glm::vec3{gris};
        }
    }
}


int main()
{
    sil::Image image{"images/logo.png"};
    //sil::Image image{300/*width*/, 200/*height*/};
    //sil::Image image{500/*width*/, 500/*height*/};
    //keep_green_only(image);
    //color_switch(image);
    //black_and_white(image);
    //negatif(image);
    //degrade(image);
    //mirror(image);
    //noise(image);
    //rotation(image);
    //rgb_split(image);
    //luminosite(image, 2.0f);
    //disque(image, 100);
    //cercle(image, 100, 10,20,2);
    //rosace(image,100, 4);
    //image.save("output/pouet.png");
    //int nb_frames = 50;
    //for (int i{0}; i < nb_frames; i++){
        //sil::Image image{500/*width*/, 500/*height*/};
        //int centre_x = (image.width() * i) / nb_frames;
        //int centre_y = image.height() / 2;
        //disque2(image, centre_x, centre_y,50);       
        //image.save("./output/frame_" + std::to_string(i) + ".png");
    //}
    mosaique(image, 5);
    //mosaique_miroir(image,5);
    //glitch(image);
    //tri(image);
    //tri_lignes(image);
    //tri_random(image);
    //mandelbrot(image);
    image.save("output/pouet20.png");
}





