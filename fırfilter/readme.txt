

FIR_filter.cpp ; programa verilen .wav uzantılı dosyayı 
kullanıcı tarafından girilen katsayilar ile filtreler ve çıkış olarak 
.wav uzantılı yeni bir dosya oluşturur.

Kullanıcı filtrelenecek .wav dosyasının ismini girmelidir. ex. "sum.wav"
Kullanıcı FIR filtre katsayılarını 2 şekilde girebilir. Komut satırından veya 
örnek olarak verilen input.txt doyasının içerisinden verebilir.

read_wav fonksiyonu .wav dosyasını okur ve gerekli bilgileri
elde eder.
write_wav fonksiyonu .wav uzantılı filtrelenmiş ses dosyasını oluşturur.
 
FIR filtreleme işlemi main() içerisinde yapılmıştır.

Kaynak:
https://www2.cs.uic.edu/~i101/SoundFiles/
https://github.com/seanmullery/DFT-and-Filtering-of-WAV-file/blob/master/filteringAnalysis.c
https://sestevenson.wordpress.com/2009/10/01/implementation-of-fir-filtering-in-c-part-1/
https://github.com/shostak-ss/FIR-filter/blob/master/Main.c