# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.GridApp.Debug:
PostBuild.ciCubeMap.Debug: /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Debug/GridApp.app/Contents/MacOS/GridApp
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Debug/GridApp.app/Contents/MacOS/GridApp:\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Debug/libciCubeMap.a\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_system.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_filesystem.a
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Debug/GridApp.app/Contents/MacOS/GridApp


PostBuild.ciCubeMap.Debug:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Debug/libciCubeMap.a:
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Debug/libciCubeMap.a


PostBuild.GridApp.Release:
PostBuild.ciCubeMap.Release: /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Release/GridApp.app/Contents/MacOS/GridApp
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Release/GridApp.app/Contents/MacOS/GridApp:\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Release/libciCubeMap.a\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_system.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_filesystem.a
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/Release/GridApp.app/Contents/MacOS/GridApp


PostBuild.ciCubeMap.Release:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Release/libciCubeMap.a:
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Release/libciCubeMap.a


PostBuild.GridApp.MinSizeRel:
PostBuild.ciCubeMap.MinSizeRel: /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/MinSizeRel/GridApp.app/Contents/MacOS/GridApp
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/MinSizeRel/GridApp.app/Contents/MacOS/GridApp:\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/MinSizeRel/libciCubeMap.a\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_system.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_filesystem.a
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/MinSizeRel/GridApp.app/Contents/MacOS/GridApp


PostBuild.ciCubeMap.MinSizeRel:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/MinSizeRel/libciCubeMap.a:
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/MinSizeRel/libciCubeMap.a


PostBuild.GridApp.RelWithDebInfo:
PostBuild.ciCubeMap.RelWithDebInfo: /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/RelWithDebInfo/GridApp.app/Contents/MacOS/GridApp
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/RelWithDebInfo/GridApp.app/Contents/MacOS/GridApp:\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/RelWithDebInfo/libciCubeMap.a\
	/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_system.a\
	/Users/mark/code/cinder_master/lib/macosx/libboost_filesystem.a
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/GridApp/RelWithDebInfo/GridApp.app/Contents/MacOS/GridApp


PostBuild.ciCubeMap.RelWithDebInfo:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/RelWithDebInfo/libciCubeMap.a:
	/bin/rm -f /Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/RelWithDebInfo/libciCubeMap.a




# For each target create a dummy ruleso the target does not have to exist
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Debug/libciCubeMap.a:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/MinSizeRel/libciCubeMap.a:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/RelWithDebInfo/libciCubeMap.a:
/Users/mark/code/cinder_master/blocks/ciCubeMap/samples/Grid/xcode/Release/libciCubeMap.a:
/Users/mark/code/cinder_master/lib/macosx/Debug/libcinder.a:
/Users/mark/code/cinder_master/lib/macosx/libboost_filesystem.a:
/Users/mark/code/cinder_master/lib/macosx/libboost_system.a:
