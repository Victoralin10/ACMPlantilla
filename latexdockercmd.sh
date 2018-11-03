#!/bin/sh
#IMAGE=blang/latex:ubuntu
IMAGE=blang/latex:latest # warning, its size is 3GB, TODO: use ubuntu image(?)
exec docker run --rm -i --user="$(id -u):$(id -g)" --net=none -v "$PWD":/data "$IMAGE" "$@"
