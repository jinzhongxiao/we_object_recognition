#!/usr/bin/env python
import roslib
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import numpy as np
import argparse
import os
import time
class image_converter:

  def __init__(self, path):
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/rgbd_camera/rgb/image_raw",Image,self.callback)
    self.image_resize = np.zeros((256,256,3))
    self.path = path
    self.count = 0
    self.last = -1
    self.occupy = [0 for i in range(0,100000)]
    rospy.Subscriber("/rotate_count", String, self.strCallback)


  def callback(self,data):
    try:
      cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
      print(e)

    self.image_resize = cv2.resize(cv_image,(256,256),interpolation=cv2.INTER_CUBIC)
  def strCallback(self, data):
    num = int(data.data)
    if self.occupy[num] == 0:
        if self.image_resize.any():
            cv2.imwrite(self.path +"/"+str(time.time())+str(num)+".jpg",self.image_resize)
            self.count += 1
            print self.count, num
        self.occupy[num] = 1





def main(args):

  parser = argparse.ArgumentParser()

  parser.add_argument('-p','--path')
  args = parser.parse_args()
  path = args.path

  ic = image_converter(path)


  rospy.init_node('image_converter', anonymous=True)
  rate =rospy.Rate(4)
  while not rospy.is_shutdown():

    cv2.imshow("Image window", ic.image_resize)
    cv2.waitKey(3)



    # rospy.loginfo(count)
    rate.sleep()


    # try:
  #   rospy.spin()
  # except KeyboardInterrupt:
  #   print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
    print "ok"
