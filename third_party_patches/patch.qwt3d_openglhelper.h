--- qwtplot3d/include/qwt3d_openglhelper.h	2005-07-19 08:40:28.000000000 -0700
+++ patched_qwt3d_openglhelper.h	2014-06-21 18:02:56.901740730 -0700
@@ -7,6 +7,7 @@
 #else
 #include <QtOpenGL/qgl.h>
 #endif
+#include <GL/glu.h>
 
 namespace Qwt3D
 {
