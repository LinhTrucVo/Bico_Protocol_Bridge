#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Path to devcontainer directory for Docker-related files
DEVCONTAINER_DIR="$SCRIPT_DIR/../.devcontainer"

echo Selecting option to build docker image.
echo "1. Using image with latest esp-idf version"
echo "2. Using image with specific esp-idf version"
echo



if [ -n "$1" ]; then
    choice="$1"
    echo "Choice provided as argument: $choice"
else
    read -p "Enter your choice (1 or 2): " choice
fi

# Delete Dockerfile and devcontainer.json if they exist in the current folder
rm -f $DEVCONTAINER_DIR/Dockerfile $DEVCONTAINER_DIR/devcontainer.json $DEVCONTAINER_DIR/entrypoint.sh

# Function to download Docker files
download_docker_files() {
    curl -L -o $DEVCONTAINER_DIR/Dockerfile https://raw.githubusercontent.com/espressif/esp-idf/master/tools/docker/Dockerfile
    curl -L -o $DEVCONTAINER_DIR/entrypoint.sh https://raw.githubusercontent.com/espressif/esp-idf/master/tools/docker/entrypoint.sh
}

if [ "$choice" == "1" ]; then
    cp $DEVCONTAINER_DIR/template/devcontainer_original.json $DEVCONTAINER_DIR/devcontainer.json
    download_docker_files
elif [ "$choice" == "2" ]; then
    cp $DEVCONTAINER_DIR/template/devcontainer_customized.json $DEVCONTAINER_DIR/devcontainer.json
    download_docker_files
else
    echo "Invalid choice."
fi

echo "Done."