#!/usr/bin/env bash

cmake .
make Client
make Server

echo "Creating $1 directory"
mkdir -p $1
mv Client $1
mv Server $1
cp -r config $1
cp -r maps $1
cp -r plugins $1
cp -r client/rendering/assets $1
cp -r client/sound_sys/sounds $1
cp client/rendering/interfaces/arcade.ttf $1
cp client/rendering/interfaces/ka1.ttf $1

cd $1
mkdir -p client/rendering
mkdir -p client/sound_sys
mkdir -p client/rendering/interfaces

mv assets client/rendering
mv sounds client/sound_sys
mv arcade.ttf client/rendering/interfaces
mv ka1.ttf client/rendering/interfaces

echo "Installation done, play well !"

