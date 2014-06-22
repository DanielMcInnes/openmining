--- qt3d/src/threed/painting/qglpainter.cpp	2014-06-21 18:30:57.477742898 -0700
+++ qglpainter.cpp	2014-06-21 18:37:21.281743216 -0700
@@ -2345,7 +2345,7 @@
 
     // Fetch the color at the specified pixel.
     unsigned char data[4] = {0, 0, 0, 0};
-    context()->functions()->glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
+    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
     QRgb color = qRgb(data[0], data[1], data[2]);
 
     // Normalize the color to account for floating-point rounding.
