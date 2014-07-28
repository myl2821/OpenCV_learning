CXXFLAGS=-I/usr/local/include/opencv -I/usr/local/include/opencv2 
LDFLAGS=-L/usr/local/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching

CXXFILES=$(shell ls *.cpp)

TARGET=$(CXXFILES:%.cpp=%)

all: $(TARGET)
	@mv $(TARGET) ./build

define gen_target
$1: $1.cpp
	$(CXX) $(CXXFLAGS) -o $$@ $$^ $(LDFLAGS)

endef

$(foreach item,  $(TARGET),  $(eval $(call gen_target,  $(item))))

clean:
	@-rm $(TARGET)

