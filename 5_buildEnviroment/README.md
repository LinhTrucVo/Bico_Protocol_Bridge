To build document:
0. Prerequisite, the bico_rst_docker submodule was cloned, if not
git submodule update --init --recursive --depth 1
1. cd 5_tools; docker build -t bico_rst -f bico_rst_docker/.devcontainer/Dockerfile bico_rst_docker/.devcontainer
2. cd ..
3. sudo docker run --rm \
-v $(pwd)/5_tools/bico_rst_docker:/workspaces/bico_rst_docker \
-v $(pwd):/workspaces/bico_rst_docker/project_doc \
bico_rst \
bash -c \
"sudo sphinx-build  -b html  \
-c /workspaces/bico_rst_docker/project_doc/docs  \
/workspaces/bico_rst_docker/project_doc  \
/tmp/doc_build && sudo cp -r /tmp/doc_build /workspaces/bico_rst_docker/_build"

docker build -t bico_rst -f ./5_tools/bico_rst_docker/.devcontainer/Dockerfile ./5_tools/bico_rst_docker/.devcontainer

CONTAINER_ID=$(docker create \
-v $(pwd):/workspaces \
bico_rst \
bash -c "sudo sphinx-build  -b html  \
-c /workspaces/docs  \
/workspaces  \
/tmp/doc_build")

docker start -a "$CONTAINER_ID"

sudo docker run --rm \
-v $(pwd)/5_tools/bico_rst_docker:/workspaces/bico_rst_docker \
-v $(pwd):/workspaces/bico_rst_docker/project_doc \
bico_rst \
bash -c \
"sudo sphinx-build  -b html  \
-c /workspaces/bico_rst_docker/project_doc/docs  \
/workspaces/bico_rst_docker/project_doc  \
/tmp/doc_build && sudo cp -r /tmp/doc_build /workspaces/bico_rst_docker/_build"