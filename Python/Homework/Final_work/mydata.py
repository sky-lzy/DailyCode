import torchvision
import torch.nn as nn
from PIL import Image
from torch.utils.data import Dataset
import os

from torchvision import transforms
from torchvision.transforms.transforms import Resize

class MyData(Dataset):

    def __init__(self, flag):
        super(Dataset, self).__init__()

        male_file = open('label\\male_names.txt', 'r')
        female_file = open('label\\female_names.txt', 'r')
        male_str = male_file.read()
        female_str = female_file.read()
        self.male = male_str.split('\n')
        self.female = female_str.split('\n')
        if flag == True:
            self.male = self.male[::2]
            self.female = self.female[::2]
        else:
            self.male = self.male[1::2]
            self.female = self.female[1::2]

        self.data_dir = 'data'

        self.transform = torchvision.transforms.Compose([
            torchvision.transforms.Resize((227, 227)),
            torchvision.transforms.ToTensor()])

        male_file.close()
        female_file.close()

    def __getitem__(self, index):
        name = None
        label = None
        size = len(self.male)

        if index < size:
            name = self.male[index]
            label = 0
        else:
            name = self.female[index - size]
            label = 1
        
        name_list = name.split('_')
        name_str = ''
        for i in range(len(name_list) - 1):
            if i != 0:
                name_str += '_'
            name_str += name_list[i]
        
        image = Image.open(os.path.join(self.data_dir, name_str, name))
        image.convert('RGB')
        image = self.transform(image)

        return image, label

    
    def __len__(self):
        return len(self.male) + len(self.female)