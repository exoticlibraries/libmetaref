
rm -Rf build/
python -m sphinx  -b html -d build/doctrees   ./ build/html
doxygen
#cp ../installscripts/cester.ps1 ./build/html/
#cp ../installscripts/cester.sh ./build/html/
touch ./build/html/.nojekyll