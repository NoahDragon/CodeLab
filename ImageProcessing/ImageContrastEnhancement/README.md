ColorImageHE.py
=============================

Color Image Histogram Equalization by Absolute Discounting Back-off

Ref(s):

 N. Bassiou, C. Kotropoulos, "Color Image Histogram Equalization by 
 Absolute Discounting Back-off". Computer Vision and Image Understanding,
 VOL. 107, pp. 108-122(2007).

2013 Mar

GCEHistMod.py
=========================

GCE Histogram Modification Algorithm for Image Contrast Enhancement

Ref(s):

	T. Arici, S. Dikbas, and Y. Altunbasak, "A Histogram Modfication Framework
	and Its Application for Image Contrast Enhancement". IEEE Trans. on IMAGE 
	PROCESSING, VOL. 18, NO. 9, pp. 1921-1935(2009).

Input: 

 8-bit gray image (array); enhancement level; threshold for two lagged difference;
 b&w stretch parameters black, white, a.

Output: 

 modified image (array)

2013 Feb

Summary
========================

In  GCEHistMod.py file (implementing the algorithm described in the paper adaptColourHE.pdf):

 gcehistmod ( img, enhancement, threshold, black, white, a, nbr_bins=256 )

Prameter: 

 8-bit gray image (array); enhancement level; threshold for two lagged difference; b&w stretch parameters black, white, a.
 
Return:

 modified image(array)

In ColorImageHE.py file  (implementing the algorithms described in the paper Bassiou07a.pdf):

 hsihe_i ( img, ibins=256, sbins=256 ) : Method III in the paper
 hsihe_si ( img, ibins=256, sbins=256 ): Method IV in the paper
 
However, this method seems work well on certain pictures. In the attachments BadPerformance.jpg and WellPerformed.jpg show the bad and good application respectively. I don't know what caused this problem.
