set -e
g++ -std=c++17 -o GetLatex GetLatex.cpp -O2
./GetLatex $1 > Library.tex
mkdir -p ../PDF
rubber -d -f Library
if [ -f Library.pdf ]; then
	mv Library.pdf ../PDF/
else
	echo "Warning: Library.pdf not found after build."
fi
mv Library.tex ../PDF/
rm -f tmp.cpp
rm -f GetLatex Library.aux Library.toc Library.out
