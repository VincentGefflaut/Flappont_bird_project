#include "gemtity.h"
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
#include <cmath>
#include <QImage>
#include <cstdlib>
#include <ctime>
#include<iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Méthodes de la classe GEMtity
bool GEMtity::collision(GEMtity* entity){
    for (int i = 0; i <= hitbox.size(); i++){
        QPointF point = hitbox.at(i);
        // On va maintenant vérifier si ce point est dans la hitbox de l'entité en argument
        auto in = std::find(entity->hitbox.begin(), entity->hitbox.end(), point);
        if( in != entity->hitbox.end()){
            return (true);
        }
        }
    }

void GEMtity::setImage(string chemin){
    load(image,chemin);
}
void GEMtity::setBehaviour(double new_pos[2],  double new_speed[2], double new_acc[2]){
    pos[0] = new_pos[0];
    pos[1] = new_pos[1];
    speed[0] = new_speed[0];
    speed[1] = new_speed[1];
    acc[0] = new_acc[0];
    acc[1] = new_acc[1];
    for (int i = 0; i<hitbox.size(); i++ ){
        hitbox[i] = hitbox[i] + QPointF(new_pos[0]-pos[0], new_pos[1]-pos[1]);
    }
}

void GEMtity::setPos(double new_pos[2]){
    setBehaviour(new_pos, speed, acc);
}
void GEMtity::setSpeed(double new_speed[2]){
    setBehaviour(pos, new_speed, acc);
}
void GEMtity::setAcc(double new_acc[2]){
    setBehaviour(pos, speed, new_acc);
}
// Constructeur de la classe GEMtity
GEMtity::GEMtity(string path, double new_pos[2], double new_speed[2], double new_acc[2]){
    // Définition de la position, vitesse, accélération et récupération de l'image
    chemin_image = path;
    pos[0] = new_pos[0];
    pos[1] = new_pos[1];
    speed[0] = new_speed[0];
    speed[1] = new_speed[1];
    acc[0] = new_acc[0];
    acc[1] = new_acc[1];
    load(image, path);
    // Construction de la hitbox
    for (int y = new_pos[1]-(image.width()+1)/2; y < new_pos[1]+(image.width()+1)/2; y++) {
        for (int x = new_pos[0]-(image.width()+1)/2; x < new_pos[0]+(image.width()+1)/2; x++) {// On effectue une détection de transparence sur le plus petit rectangle contenant tout l'image
            Color pixel = image(x, y);
            if (pixel.r() == 0 && pixel.g() == 0 && pixel.b() == 0) { // On vérifie que le pixel est transparent ie rouge, vert et bleu nul
                hitbox.append(QPointF(x, y));//On ajoute le point à notre hitbox
            }
        }
    }
}
void GEMtity::display(){
    Imagine::display(image,pos[0],pos[1]);
}

void GEMtity::refresh(double time_now){
    double nouv_pos[2]={pos[0] + pow(time_now,2)/2*acc[0] + time_now*speed[0],
                        pos[1] + pow(time_now,2)/2*acc[1] + time_now*speed[1]};
    setPos(nouv_pos);
    double nouv_speed[2] = {speed[0] + time_now*acc[0],
                           speed[1] + time_now*acc[1]};
    setSpeed(nouv_speed);

}
