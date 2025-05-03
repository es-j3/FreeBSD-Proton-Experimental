--- dlls/ntdll/unix/loader.c.orig	2025-04-29 18:52:18.000000000 -0700
+++ dlls/ntdll/unix/loader.c		2025-05-01 19:10:00.052033000 -0700
@@ -557,6 +557,22 @@
 
     if (machine == current_machine) return NULL;
 
+    char* wineserver_path = getenv("WINESERVER");
+    if (wineserver_path != NULL && wineserver_path[0] == '/') {
+        char* s = remove_tail(wineserver_path, "server");
+        if (s != NULL) {
+            if (machine == IMAGE_FILE_MACHINE_AMD64) {
+                ret = malloc(strlen(s) + 3);
+                strcpy(ret, s);
+                strcat(ret, "64");
+            } else {
+                ret = s;
+            }
+            return ret;
+        }
+    }
+
+
     /* try the 64-bit loader */
     if (current_machine == IMAGE_FILE_MACHINE_I386 && machine == IMAGE_FILE_MACHINE_AMD64)
     {
