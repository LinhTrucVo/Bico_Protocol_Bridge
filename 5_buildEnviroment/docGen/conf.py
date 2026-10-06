
project = 'Bico Protocol Bridge'
copyright = '2025, Bico'
author = 'Bico'
release = '1.0'

master_doc = "5_buildEnviroment/docGen/index"

extensions = [
    'sphinxcontrib.plantuml',
]

# Path to plantuml.jar
# plantuml = 'java -jar /usr/bin/plantuml.jar'
plantuml = 'plantuml'

templates_path = ['_templates']
exclude_patterns = []

html_theme = 'sphinx_rtd_theme'