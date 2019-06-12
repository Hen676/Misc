# -*- coding: utf-8 -*-

import Augmentor

p = Augmentor.Pipeline("/Users/thehe/Desktop/Project/Images/OPRL/yes")

p.random_distortion(probability=1, grid_width=4, grid_height=4, magnitude=3)
p.rotate(probability=1, max_left_rotation=5, max_right_rotation=5)

p.sample(1000)