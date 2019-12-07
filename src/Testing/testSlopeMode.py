
import os
import math
import pydicom

def subdir_list(dirname):
    """获取目录下所有子目录名
    :param dirname: str 目录的完整路径
    :return: list(str) 所有子目录的完整路径组成的列表
    """
    sub_dir = list(filter(os.path.isdir,
                map(lambda filename: os.path.join(dirname, filename),
                    os.listdir(dirname))))
    result = []
    for str in sub_dir:
        result.append(str.replace('\\', '/'))

    return result

def file_list(dirname, ext=".dcm"):
    """获取目录下所有特定后缀的文件
    :param dirname:str 目录的完整路径
    :param ext: str后缀名，以点号分开
    :return:list(str) 所有子文件名组成的列表
    """
    files = list(filter(lambda filename: os.path.splitext(filename)[1] == ext, os.listdir(dirname)))

    result = []
    for str in files:
        result.append(dirname + "/" + str)

    return result

def dicom_file_list(dirname):
    """ 获取目录下所有的dicom文件，按照位置关系前后排列
    :param dirname:包含dicom文件夹目录
    :return:diet(double:str) 所有dicom文件组成的字典文件
    """
    files = file_list(dirname, "")
    fileMap = {}

    for file in files:
        ds = pydicom.dcmread(file)
        orientation = ds[0x20, 0x37].value
        position = ds[0x20, 0x32].value

        p = []
        for i in orientation:
            p.append(float(i))

        norm = [1 , 0 , 0]
        norm[0] = math.fabs(float(p[1] * p[5] - p[4] * p[2]))
        norm[1] = math.fabs(float(p[3] * p[2] - p[0] * p[5]))
        norm[2] = math.fabs(float(p[0] * p[4] - p[3] * p[1]))

        if norm[2] > norm[1] and norm[2] > norm[0]:
            fileMap[float(position[2])] = file
        elif norm[1] > norm[2] and norm[1] > norm[0]:
            fileMap[float(position[1])] = file
        else:
            fileMap[float(position[0])] = file

    return fileMap

input_path = "F:/上海六院项目/张仁君 术前/PA1/ST0/SE0"
output_path = "E:/Wheel/PerfusionImaging/Data/PreOperation/"

sub_paths = subdir_list(input_path)

origin_files = dicom_file_list(sub_paths[0])

for i in range(7, len(sub_paths)):
    print(sub_paths[i])
    files = dicom_file_list(sub_paths[i])

    base_path = os.path.basename(sub_paths[i])
    output_sub_path = output_path + base_path

    if not os.path.exists(output_sub_path):
        os.makedirs(output_sub_path)

    for key, value in files.items():
        ds_cur = pydicom.dcmread(value)
        ds_orig = pydicom.dcmread(origin_files[key])

        ds_output = ds_cur;
        ds_output.RescaleIntercept = 0

        for n, val in enumerate(ds_output.pixel_array.flat):  # example: zero anything < 300
                ds_output.pixel_array.flat[n] = ds_cur.pixel_array.flat[n] - ds_orig.pixel_array.flat[n]

        ds_output.PixelData = ds_output.pixel_array.tostring()

        base_name = os.path.basename(value)
        out_name = output_sub_path + "/" + base_name
        ds_output.save_as(out_name)



















