#!/usr/bin/env python

import rospy
import cv2
import numpy as np
import message_filters
import actionlib
import time
import math

from sensor_msgs.msg import LaserScan, Image
from geometry_msgs.msg import Twist
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from cv_bridge import CvBridge

# rgby detected vars
r = 0
g = 0
b = 0
y = 0
# move_base check
num = 0
num_check = 1
# pos changer vars
x_level = 0
y_level = 0
flip = True

def region(msg):
    #640 split between 5 parts
    regions = [
    min(min(msg.ranges[0:128]),5),#right
    min(min(msg.ranges[128:256]),5),
    min(min(msg.ranges[256:384]),5),
    min(min(msg.ranges[384:512]),5),
    min(min(msg.ranges[512:640]),5),#left
    ]

    # nan values to zero
    for temp in range(0,5):
        if math.isnan(regions[temp]):
            regions[temp] = float(0)

    return regions

def found(laser,data):

    regions = region(laser)

    global r, g, b, y, num

    cv_image = bridge.imgmsg_to_cv2(data, "bgr8")

    # Colour boundary's
    r_lower = np.array([0, 0, 102])
    r_upper = np.array([10, 10, 255])
    g_lower = np.array([0, 102, 0])
    g_upper = np.array([10, 255, 10])
    b_lower = np.array([102, 0, 0])
    b_upper = np.array([255, 10, 10])
    y_lower = np.array([0, 102, 102])
    y_upper = np.array([10, 255, 255])

    # Create mask
    r_mask = cv2.inRange(cv_image, r_lower, r_upper)
    g_mask = cv2.inRange(cv_image, g_lower, g_upper)
    b_mask = cv2.inRange(cv_image, b_lower, b_upper)
    y_mask = cv2.inRange(cv_image, y_lower, y_upper)

    # Colour count
    r_n = 0
    g_n = 0
    b_n = 0
    y_n = 0
    if r == 0:
        r_n = np.count_nonzero(r_mask)
    if g == 0:
        g_n = np.count_nonzero(g_mask)
    if b == 0:
        b_n = np.count_nonzero(b_mask)
    if y == 0:
        y_n = np.count_nonzero(y_mask)

    msg = Twist()

    lin_x = 0
    ang_z = 0
    can1 = False

    #detect if any colour is present
    if r_n >= 5000 or g_n >= 5000 or b_n >= 5000 or y_n >= 5000:
        if r_n >= 70000 or g_n >= 70000 or b_n >= 70000 or y_n >= 70000:
            # 70,000 = found post plus check front > 1m
            if r_n >= 70000 and regions[2] < 1:
                rospy.loginfo("Red Found")
                r = 1
                can1 = True
            elif g_n >= 70000 and regions[2] < 1:
                rospy.loginfo("Green Found")
                g = 1
                can1 = True
            elif b_n >= 70000 and regions[2] < 1:
                rospy.loginfo("Blue Found")
                b = 1
                can1 = True
            elif y_n >= 70000 and regions[2] < 1:
                rospy.loginfo("Yellow Found")
                y = 1
                can1 = True
            else:
                can1 = True
                rospy.loginfo("Skip, next to completed color")
        else: #head towards side with least colour or forward if colour is in the middle
            if r_mask[240,320] != 0 or g_mask[240,320] != 0 or b_mask[240,320] != 0 or y_mask[240,320] != 0:
                lin_x = 0.3
                ang_z = 0
            elif r_n >= 2000:
                if np.count_nonzero(r_mask[:,0:340]) > np.count_nonzero(r_mask[:,300:640]):
                    lin_x = 0
                    ang_z = 0.2
                else:
                    lin_x = 0
                    ang_z = -0.2
            elif g_n >= 2000:
                if np.count_nonzero(g_mask[:,0:340]) > np.count_nonzero(g_mask[:,300:640]):
                    lin_x = 0
                    ang_z = 0.2
                else:
                    lin_x = 0
                    ang_z = -0.2
            elif b_n >= 2000:
                if np.count_nonzero(b_mask[:,0:340]) > np.count_nonzero(b_mask[:,300:640]):
                    lin_x = 0
                    ang_z = 0.2
                else:
                    lin_x = 0
                    ang_z = -0.2
            elif y_n >= 2000:
                if np.count_nonzero(y_mask[:,0:340]) > np.count_nonzero(y_mask[:,300:640]):
                    lin_x = 0
                    ang_z = 0.2
                else:
                    lin_x = 0
                    ang_z = -0.2
            else:
                can1 = True
                rospy.loginfo("Failure_2")
    else:
        can1 = True
        rospy.loginfo("Nothing found/No Path")

    if r == 1 and g == 1 and b == 1 and y == 1: #finish if all poles are found
        rospy.loginfo("Done all")
        rospy.spin()

    msg.linear.x = lin_x
    msg.angular.z = ang_z
    pub.publish(msg)

    if can1:
        navigate()

def navigate ():
    global num_check, num, x_level, y_level, flip

    num = num + 1 #objective tracker

    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    client.wait_for_server()

    goal = MoveBaseGoal()
    # set target grid
    pos_y = [-4,-2,0,2,4]
    pos_x = [-4,-2,0,2,4]

    if flip == 0: #flip orientation
        if y_level == 1 or y_level == 3: #work zig zag pattern
            target_pos_x = -pos_x[x_level]
        else:
            target_pos_x = pos_x[x_level]
        target_pos_y = pos_y[y_level]

        # goal config
        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose.position.x = target_pos_x
        goal.target_pose.pose.position.y = target_pos_y
        goal.target_pose.pose.position.z = 0
        goal.target_pose.pose.orientation.w = 1
        goal.target_pose.pose.orientation.z = 1

        flip = 1
    elif flip == 1:
        if y_level == 1 or y_level == 3:
            target_pos_x = -pos_x[x_level]
        else:
            target_pos_x = pos_x[x_level]
        target_pos_y = pos_y[y_level]

        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose.position.x = target_pos_x
        goal.target_pose.pose.position.y = target_pos_y
        goal.target_pose.pose.position.z = 0
        goal.target_pose.pose.orientation.w = 1
        goal.target_pose.pose.orientation.z = 0

        flip = 2
    elif flip == 2:
        if y_level == 1 or y_level == 3:
            target_pos_x = -pos_x[x_level]
        else:
            target_pos_x = pos_x[x_level]
        target_pos_y = pos_y[y_level]

        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose.position.x = target_pos_x
        goal.target_pose.pose.position.y = target_pos_y
        goal.target_pose.pose.position.z = 0
        goal.target_pose.pose.orientation.w = 1
        goal.target_pose.pose.orientation.z = -1

        flip = 3
    elif flip == 3:
        if y_level == 1 or y_level == 3:
            target_pos_x = -pos_x[x_level]
        else:
            target_pos_x = pos_x[x_level]
        target_pos_y = pos_y[y_level]

        if x_level == 4: #level adjuster 23 -> 24 -> 31
            x_level = 0
            if y_level == 4:
                y_level = 0
            else:
                y_level = y_level + 1
        else:
            x_level = x_level + 1

        goal.target_pose.header.frame_id = "map"
        goal.target_pose.header.stamp = rospy.Time.now()
        goal.target_pose.pose.position.x = target_pos_x
        goal.target_pose.pose.position.y = target_pos_y
        goal.target_pose.pose.position.z = 0
        goal.target_pose.pose.orientation.w = 0
        goal.target_pose.pose.orientation.z = 1

        flip = 0

    if num_check == num: #check objective
        client.send_goal(goal)

        wait = client.wait_for_result()
        if not wait:
            rospy.loginfo("Action Server Error")
        else:
            rospy.loginfo("Done")
            num_check = num_check + 1
            return client.get_result()

def main():
    global bridge, pub

    bridge = CvBridge()

    rospy.init_node('Main')

    sub1 = message_filters.Subscriber('/scan', LaserScan)
    sub2 = message_filters.Subscriber('/camera/rgb/image_raw', Image)
    sub = message_filters.TimeSynchronizer([sub1, sub2], 10)
    sub.registerCallback(found)

    pub = rospy.Publisher('/mobile_base/commands/velocity', Twist, queue_size=1)

    rospy.spin()

if __name__ == '__main__':
    main()
