logging_prefix="[unitTestBuild] "

echo "${logging_prefix}Clone bico_gtest_docker submodule"
git submodule update --init ./5_buildEnviroment/unitTestBuild/bico_gtest_docker

echo "${logging_prefix}Build bico_gtest_docker image"

IMAGE_NAME="bico_gtest"
if docker image inspect "$IMAGE_NAME" > /dev/null 2>&1; then
    echo "Docker image '$IMAGE_NAME' already exists. Skipping build."
else
    echo "Docker image '$IMAGE_NAME' does not exist. Building..."
    docker build \
        -t "$IMAGE_NAME" \
        -f ./5_buildEnviroment/unitTestBuild/bico_gtest_docker/.devcontainer/Dockerfile \
        ./5_buildEnviroment/unitTestBuild/bico_gtest_docker/.devcontainer
fi

echo "${logging_prefix}Create Bico_Protocol_Bridge_unittestBuild container"
docker container inspect Bico_Protocol_Bridge_unittestBuild > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "${logging_prefix}Container exists"
else
    echo "${logging_prefix}Container does not exist, create container..."
    docker create --name Bico_Protocol_Bridge_unittestBuild \
    -v $(pwd)/5_buildEnviroment/unitTestBuild/bico_gtest_docker:/workspaces/bico_gtest_docker \
    -v $(pwd):/workspaces/bico_gtest_docker/project_under_test \
    bico_gtest \
    bash -c "/workspaces/bico_gtest_docker/tool/coverage.sh /workspaces/bico_gtest_docker/project_under_test/5_buildEnviroment/unitTestBuild"
fi

echo "${logging_prefix}Start Bico_Protocol_Bridge_unittestBuild container and build unittest"
mkdir -p _build
docker start -a Bico_Protocol_Bridge_unittestBuild
docker cp "Bico_Protocol_Bridge_unittestBuild":/workspaces/bico_gtest_docker/_build ./_build/unitTestBuild
