Digital Video Processing <!-- omit in toc -->
===

**Table of Contents**
- [1. Numpy](#1-numpy)
  - [1.1. Create Array](#11-create-array)
  - [1.2. Manipulate Array](#12-manipulate-array)
  - [1.3. Random](#13-random)
- [2. OpenCV](#2-opencv)
  - [2.1. Windows and mouse/key](#21-windows-and-mousekey)
  - [2.2. Trackbar](#22-trackbar)
  - [2.3. Drawing](#23-drawing)
  - [2.4. Image Files](#24-image-files)
  - [2.5. Matplotlib](#25-matplotlib)
  - [2.6. Advanced Manipulation](#26-advanced-manipulation)
- [#. final term study](#-final-term-study)
    - [chapter 7](#chapter-7)
    - [chapter 8](#chapter-8)
    - [chapter 9](#chapter-9)
    - [chapter 10](#chapter-10)
    - [chapter 11](#chapter-11)
    - [chapter 12](#chapter-12)

# 1. Numpy
## 1.1. Create Array
```python
import numpy as np

list_a = [1, 2, 3]

shape = (300, 400)
dtype = np.uint8

image = np.array(list_a)

image = np.zeros(shape, dtype)
image = np.ones (shape, dtype)
image = np.empty(shape, dtype)
image = np.full (shape, fill_value, dtype)

image.fill(value)

print(image.shape[0], image.shape[1])
```

## 1.2. Manipulate Array
```python
import numpy as np

newshape = (100, 200)

np.reshape(array, newshape)

array.flatten()  # only flatten copys
np.ravel(array)
np.reshape(array, (-1,))
array.reshape(-1,)
```

## 1.3. Random
```python
import numpy as np

seed = 100
shape = (2, 3)

np.random.seed(seed)
np.random.rand(shape)
np.random.randn(shape)
np.random.randint(low, high, shape)
```

# 2. OpenCV
## 2.1. Windows and mouse/key
```python
import cv2

title = "Window Title"
x, y = 100, 150
image = np.zeros(shape, dtype)
image.fill(value)

# create and manipulate
cv2.namedWindow(title[, {cv2.WINDOW_AUTOSIZE | cv2.WINDOW_NORMAL}])
cv2.moveWindow(title, x, y)
cv2.resizeWindow(title, width, height)
cv2.imshow(title, image)

# mouse event handler
def onMouse(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        pass

cv2.setMouseCallback(windowName=title, onMouse)

# wait for key and exit
cv2.waitKey(key)
cv2.waitKeyEx(delay)  # wait for delay, ret : pressed key, except KeyError
cv2.destroyAllWindows()
```

## 2.2. Trackbar
```python
import cv2

title = "Trackbar Event"
image = np.zeros(...)

def onChange(value):
    global image
    pass

cv2.createTrackbar(
    trackbarName,
    windowName=title,
    value,  # init value
    count,  # level count
    onChange  # cb function
)
cv2.setTrackbarPos(
    trackbarName,
    windowName=title,
    pos
)
cv2.getTrackbarPos(
    trackbarName,
    windowName=title,
)
```

## 2.3. Drawing
```python
import cv2

cv2.line(image, pt1, pt2, color)
cv2.rectangle(iimage, pt1, pt2, color[, thickness][, {cv2.LINE_AA | cv2.LINE_4 | cv2.LINE_8}])  # pt1, pt2 can be replaced to (x, y, w, h)

cv2.circle(image, center, radius, color, thickness)
axes = (120, 60)  # x_radius, y_radius
cv2.ellipse(image, center, axes, angle, startAngle, endAngle, color, thickness)  # start/endAngle : starts from y axis

cv2.putText(image, text, org, fontFace, fontScale, color, ...)  # ort : pos of left bottom of text
```

## 2.4. Image Files
```python
import cv2

image = cv2.imread(filename, cv2.IMREAD_COLOR)
if (image is None):
    raise Exception("Error")

print(image.dtype, image.ndim)
cv2.imshow(title, image)

param = (cv2.IMWRITE_JPEG_QUALITY, 10)
cv2.imwrite(filename, image[, param])
```
```python
import cv2

image8 = cv2.imread(filename, cv2.IMREAD_COLOR)
image16 = np.uint16(image8 * (65535/255))
image32 = np.float32(image8 * (1/255))

cv2.imwrite(filename16, image16)
cv2.imwrite(filename32, image32)

cv2.imshow(winname16, image16)
cv2.imshow(winname32, (image32 * 255).astype("uint8"))
```

## 2.5. Matplotlib
```python
import cv2
import matplotlib.pyplot as plt

image = cv2.imread(filename, cv2.IMREAD_COLOR)
rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

fig = plt.figure(num=1, figsize=(3,4))
plt.imshow(image)
plt.title("BGR")
plt.show()
```

## 2.6. Advanced Manipulation
```python
import cv2

image = cv2.imread(filename, cv2.IMREAD_COLOR)

cv2.flip(image, flipCode)
# flipCode
# 0 : x_axis
# 1 : y_axis
# -1 : xy_axis
cv2.repeat(image, ny, nx)
cv2.transpose(image)
```
```python
import numpy as np
import cv2

ch0 = np.zeros(shape, dtype) + 10
ch1 = np.zeros(shape, dtype) + 20
ch2 = np.zeros(shape, dtype) + 30

list_bgr = [ch0, ch1, ch2]
merge_bgr = cv2.merge(list_bgr)
split_bgr = cv2.split(merge_bgr)  # [ch0, ch1, ch2]

print(merge_bgr.shape)
print(np.array(split_bgr).shape)
```
masking
```python
import numpy as np
import cv2

m1 = np.full(shape, 10, dtype)
m2 = np.full(shape, 20, dtype)

mask = np.zeros(m1.shape, dtype)
mask[:, 3:] = 1

m_add = cv2.add(m1, m2[, mask=mask])
m_sub = cv2.subtract(m1, m2[, mask=mask])
m_mul = cv2.multiply(m1, m2[, mask=mask])
m_div = cv2.divide(m1, m2[, mask=mask])
m_div2 = cv2.divide(m1.astype(np.float32), np.float(m2)[, mask=mask])

dif_img = cv2.subtract(np.int16(m1), np.int16(m2))
abs_diff1 = np.absolute(dif_img).astype("float32")/255
abs_diff2 = cv2.absdiff(m1, m2)
```
```python
import numpy as np
import cv2

v1 = np.array(Object, dtype)  # object : list or tuple(?)
exp = cv2.exp(v1)
log = cv2.log(v1)
sqrt = cv2.sqrt(v1)
pow = cv2.pow(v1, power)

print(log.T)
```
```python
import numpy as np
import cv2

x = np.array(object, np.float32)
y = np.array(object).astype("float32")

mag, ang = cv2.magnitude(x, y), cv2.phase(x, y)
p_mag, p_ang = cv2.cartToPolar(x, y)
c_x, c_y = cv2.polarToCart(p_mag, p_ang)
```
```python
import ...

cv2.circle(image1, ...)
cv2.ractangle(image2, ...)

image3 = cv2.bitwise_or(image1, image2)
image4 = cv2.bitwise_and(image1, image2)
image5 = cv2.bitwise_xor(image1, image2)
image6 = cv2.bitwise_not(image1)

m_min = cv2.min(image, 30)
m_max = cv2.max(image, image2)
min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(image)

cv2.sumElems(image)
cv2.mean(image[, mask])
mean, stddev = cv2.meanStdDev(image[, mask])

cv2.sort(image, cv2.SORT_...)
np.sort(image, axis)
# axis
# 1 : y, 0 : x
cv2.sortIdx(image, cv2.SORT_...)
np.argsort(image, axis)

cv2.reduce(image, dim, rtype=cv2.REDUCE_...)
# dim
# 1 : x, 0 : y
```

# #. final term study
### chapter 7
```
p.289 bluring
p.293 sharpening

p.296 first order derivative mask(?)
p.298 roberts edge detection
p.301 prewitt edge detection
p.303 sobel edge detection

p.305 second order derivative mask
p.306 laplacian edge detection
p.309 LoG(Laplacian of Gaussian), DoG(Difference of Gaussian)
p.311 canny edge detection

p.318 minMax filtering
p.321 average filtering
p.324 median filtering
p.328 gaussian smoothing filtering

p.334 morphology
p.335 erosion operation
p.340 dilation operation
p.343 opening/closing operation
```

### chapter 8
```
p.360 scaling
p.363 nearest neighbor interpolation
p.365 bilinear interpolation

p.370 translation
p.373 roation

p.380 affine transform
p.386 affain combination

p.391 perspective projection transformation
```

### chapter 9
```
p.413 fourier transform
p.416 1d dft
p.422 2d dft
# before shift : inside(high), outside(low)
# after  shift : inside(low), outside(high)
# lower freq : overall
# higher freq : details
p.429 idft
p.439 fft filtering(butterworth, gaussian)

p.445 dct
p.449 forward dct
```

### chapter 10
```
p.469 hough line detection

p.476 moravec corner detection
p.478 harris corner detection

p.483 k-NN
p.499 warping, morphing
```

### chapter 11
```
p.520 paint
p.537 haar
```

### chapter 12
```
p.565 coin
p.579 plate
```