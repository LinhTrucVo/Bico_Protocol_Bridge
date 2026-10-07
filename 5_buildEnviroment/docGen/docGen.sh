logging_prefix="[docGen] "

echo "${logging_prefix}Clone bico_rst_docker submodule"
git submodule update --init ./5_buildEnviroment/docGen/bico_rst_docker

echo "${logging_prefix}Build bico_rst_docker image"

IMAGE_NAME="bico_rst"
if docker image inspect "$IMAGE_NAME" > /dev/null 2>&1; then
    echo "${logging_prefix}Docker image '$IMAGE_NAME' already exists. Skipping build."
else
    echo "${logging_prefix}Docker image '$IMAGE_NAME' does not exist. Building..."
    docker build \
        -t "$IMAGE_NAME" \
        -f ./5_buildEnviroment/docGen/bico_rst_docker/.devcontainer/Dockerfile \
        ./5_buildEnviroment/docGen/bico_rst_docker/.devcontainer
fi

echo "${logging_prefix}Create Bico_Protocol_Bridge_docGen container"
docker container inspect Bico_Protocol_Bridge_docGen > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "${logging_prefix}Container exists"
else
    echo "${logging_prefix}Container does not exist, create container..."
    docker create --name Bico_Protocol_Bridge_docGen \
    -v $(pwd):/workspaces \
    bico_rst \
    bash -c "sphinx-build  -b html  \
    -c /workspaces/5_buildEnviroment/docGen  \
    /workspaces  \
    /workspaces/_build/docGen"
fi

echo "${logging_prefix}Start Bico_Protocol_Bridge_docGen container and build documentation"
mkdir -p _build
docker start -a Bico_Protocol_Bridge_docGen
