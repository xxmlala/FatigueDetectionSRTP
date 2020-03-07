#平移
img = cv2.imread('4.jpg')
# 构造移动矩阵H
# 在x轴方向移动多少距离，在y轴方向移动多少距离
H = np.float32([[1, 0, 50], [0, 1, 25]])
rows, cols = img.shape[:2]
print(img.shape)
print(rows, cols)
res = cv2.warpAffine(img, H, (cols, rows)) 
cv2.imshow('origin_picture', img)
cv2.imshow('new_picture', res)
cv2.waitKey(0)

# 放大/缩小
img = cv2.imread('4.jpg')
# 一是通过设置图像缩放比例，即缩放因子，来对图像进行放大或缩小
res1 = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_LINEAR)
height, width = img.shape[:2]
# 二是直接设置图像的大小，不需要缩放因子
res2 = cv2.resize(img, (int(0.8*width), int(0.8*height)), interpolation=cv2.INTER_AREA)
cv2.imshow('origin_picture', img)
cv2.imshow('res1', res1)
cv2.imshow('res2', res2)
cv2.waitKey(0)

#旋转
img = cv2.imread('4.jpg')
rows, cols = img.shape[:2]
# 第一个参数是旋转中心，第二个参数是旋转角度，第三个参数是缩放比例
M1 = cv2.getRotationMatrix2D((cols/2, rows/2), 45, 0.5)
M2 = cv2.getRotationMatrix2D((cols/2, rows/2), 45, 2)
M3 = cv2.getRotationMatrix2D((cols/2, rows/2), 45, 1)
res1 = cv2.warpAffine(img, M1, (cols, rows))
res2 = cv2.warpAffine(img, M2, (cols, rows))
res3 = cv2.warpAffine(img, M3, (cols, rows))
cv2.imshow('res1', res1)
cv2.imshow('res2', res2)
cv2.imshow('res3', res3)
cv2.waitKey(0)
cv2.destroyAllWindows()

#仿射变换
img = cv2.imread('4.jpg')
rows, cols = img.shape[:2]
pts1 = np.float32([[50, 50], [200, 50], [50, 200]])
pts2 = np.float32([[10, 100], [200, 50], [100, 250]])
# 类似于构造矩阵
M = cv2.getAffineTransform(pts1, pts2)
res = cv2.warpAffine(img, M, (cols, rows))
cv2.imshow('原图', img)
cv2.imshow('res', res)
cv2.waitKey(0)

#透射变换
img = cv2.imread('4.jpg')
rows, cols = img.shape[:2]
pts1 = np.float32([[56, 65], [238, 52], [28, 237], [239, 240]])
pts2 = np.float32([[0, 0], [200, 0], [0, 200], [200, 200]])
M = cv2.getPerspectiveTransform(pts1, pts2)
res = cv2.warpPerspective(img, M, (cols, rows))
cv2.imshow('yuantu', img)
cv2.imshow('res', res)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.destroyAllWindows()
