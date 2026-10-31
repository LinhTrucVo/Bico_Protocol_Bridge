# Build environment

Run from the repository root on Linux (or WSL) with Docker. CI runs the same scripts (`.github/workflows/ci.yml`).
Each script initialises its submodule, builds the Docker image once and reuses the container.

| Purpose | Command | Output |
|---|---|---|
| Documentation (Sphinx, Sphinx-Needs, PlantUML) | `5_buildEnviroment/docGen/docGen.sh` | `_build/docGen` |
| Unit and integration tests with coverage (GoogleTest, fff, nlohmann/json) | `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` | `_build/unitTestBuild` |

| Path | Content |
|---|---|
| `docGen/conf.py`, `docGen/aspice_config.py` | Sphinx configuration, ASPICE need types, links and checks |
| `docGen/bico_rst_docker` | Submodule: documentation Docker image (read-only) |
| `unitTestBuild/CMakeLists.txt` | Test registration (`add_subdirectory` per test), nlohmann/json download |
| `unitTestBuild/halFake/` | Shared HAL fake helper (`bpbHalFake.h`) for JSON based HAL fakes |
| `unitTestBuild/bico_gtest_docker` | Submodule: test Docker image and coverage script (read-only) |

Docker caches the containers `Bico_Protocol_Bridge_docGen` and `Bico_Protocol_Bridge_unittestBuild`. Remove them (`docker rm <name>`) after changing a script.