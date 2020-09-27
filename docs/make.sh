
rm -Rf build/
python -m sphinx  -b html -d build/doctrees   ./ build/html
doxygen
touch ./build/html/.nojekyll