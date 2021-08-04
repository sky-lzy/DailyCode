import torch
import torchvision
from PIL import Image

from net import Net

image_path = "./airplane2.png"
image = Image.open(image_path)

image = image.convert('RGB')
transform = torchvision.transforms.Compose([
    torchvision.transforms.Resize((32, 32)),
    torchvision.transforms.ToTensor()
])
image = transform(image)
image = torch.reshape(image, (1, 3, 32, 32))

model = torch.load('net_CIFAR10_gpu_100.pth', map_location=torch.device('cpu'))
model.eval()
with torch.no_grad():
    output = model(image)

result = output.argmax(1).item()
print(result)