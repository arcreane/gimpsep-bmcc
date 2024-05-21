# Gimpsep

Logiciel d'édition d'image

## Table des matières

1. [Introduction](#introduction)
2. [Configuration](#Configuration)
3. [Build/Run](#Build/Run)

## Introduction

Je vais vous expliquer comment config ce projet de mort, mais ca reprend ce qu'on a fait en cours vous inquietez pas (en fait si inquietez vous)

Tout d'abord, assurez vous que le fichier main.cpp soit bien visible, sinon allez dans l'explorateur de fichier pour le rajouter dans les fichiers sources.

## Configuration


Tout d'abord, assurez vous d'avoir bien setup la variable d'environement OPENCV_PATH, qui doit mener vers votre répertoir openCV, qui fini par: 
opencv\build.


Pour vérifier la configuration du projet, vous aller aller dans "Projet" dans votre barre en haut de votre VS Community, puis dans "propriétés de gimpsep"

Tout d'abord, en haut du panel qui est apparu, il faudra passer la configuration à "Realease", et la plateforme à "x64"

Ensuite vous allez aller dans "C/C++" , puis "général", puis dans autre répertoire include vousdevez avoir le lien vers votre dossier avec openCV dedans, qui doit être:
$(OPENCV_PATH)\include


Après, vous allez dans "éditeur de lien", puis dans "général", et dans répertoire de bibliothèques suplémentaires, vous devez avoir les lien vers votre dossier avec openCV dedans, qui fini par :
$(OPENCV_PATH)\x64\vc16\lib
$(OPENCV_PATH)\x64\vc16\bin

Puis ensuite vous allez juste en dessous, dans "entrée", et dans dépendances supplémentaires vous aller rentrer :
opencv_world490.lib

Voila, vous appliquez tout ça et le tour est joué !

### Build/Run le projet

Maintenant vous pouvez fermer la fenêtre de config.

Dans la barre en haut de la vue générale de Visual Studio community, vous avez la petite flèche verte pour run, et à gauche vous avez deux options : Vous devez les passer à "Release" et "x64"

Ensuite, vous pouver run, et normalement ca devrait marcher. Sinon vous me pingez discord et je vous insultes parce vous êtes mauvais, puis je vous aide :)
