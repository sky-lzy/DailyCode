##############################################
#This implementation defines the model of multil-layer perceptron as a custom Module subclass.
##############################################

import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision.transforms import ToTensor, Lambda

training_data = datasets.FashionMNIST(
    root="./Datasets/FashionMNIST",
    train=True,
    download=True,
    transform=ToTensor()
)

test_data = datasets.FashionMNIST(
    root="./Datasets/FashionMNIST",
    train=False,
    download=True,
    transform=ToTensor()
)

train_dataloader = DataLoader(training_data, batch_size=64)
test_dataloader = DataLoader(test_data, batch_size=64)

def relu(X):
    return torch.max(input=X, other=torch.tensor(0.0))

class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.flatten = nn.Flatten()

        num_inputs, num_outputs, num_hiddens = 784, 10, 256

        self.W1 = torch.nn.Parameter(torch.randn((num_inputs, num_hiddens), dtype=torch.float))
        self.b1 = torch.nn.Parameter(torch.zeros(num_hiddens, dtype=torch.float))
        self.W2 = torch.nn.Parameter(torch.randn((num_hiddens, num_outputs), dtype=torch.float))
        self.b2 = torch.nn.Parameter(torch.zeros(num_outputs, dtype=torch.float))



    def forward(self, X):
        X = self.flatten(X)
        H = relu(torch.matmul(X, self.W1) + self.b1)
        logits = torch.matmul(H, self.W2) + self.b2
        return logits

model = NeuralNetwork()


##############################################
# Hyperparameters
# -----------------
#
# Hyperparameters are adjustable parameters that let you control the model optimization process.
# Different hyperparameter values can impact model training and convergence rates
# (`read more <https://pytorch.org/tutorials/beginner/hyperparameter_tuning_tutorial.html>`__ about hyperparameter tuning)
#
# We define the following hyperparameters for training:
#  - **Number of Epochs** - the number times to iterate over the dataset
#  - **Batch Size** - the number of data samples propagated through the network before the parameters are updated
#  - **Learning Rate** - how much to update models parameters at each batch/epoch. Smaller values yield slow learning speed, while large values may result in unpredictable behavior during training.
#

#learning_rate = 1e-3
learning_rate = 0.2
batch_size = 64
epochs = 5



#####################################
# Optimization Loop
# -----------------
#
# Once we set our hyperparameters, we can then train and optimize our model with an optimization loop. Each
# iteration of the optimization loop is called an **epoch**.
#
# Each epoch consists of two main parts:
#  - **The Train Loop** - iterate over the training dataset and try to converge to optimal parameters.
#  - **The Validation/Test Loop** - iterate over the test dataset to check if model performance is improving.
#
# Let's briefly familiarize ourselves with some of the concepts used in the training loop. Jump ahead to
# see the :ref:`full-impl-label` of the optimization loop.
#
# Loss Function
# ~~~~~~~~~~~~~~~~~
#
# When presented with some training data, our untrained network is likely not to give the correct
# answer. **Loss function** measures the degree of dissimilarity of obtained result to the target value,
# and it is the loss function that we want to minimize during training. To calculate the loss we make a
# prediction using the inputs of our given data sample and compare it against the true data label value.
#
# Common loss functions include `nn.MSELoss <https://pytorch.org/docs/stable/generated/torch.nn.MSELoss.html#torch.nn.MSELoss>`_ (Mean Square Error) for regression tasks, and
# `nn.NLLLoss <https://pytorch.org/docs/stable/generated/torch.nn.NLLLoss.html#torch.nn.NLLLoss>`_ (Negative Log Likelihood) for classification.
# `nn.CrossEntropyLoss <https://pytorch.org/docs/stable/generated/torch.nn.CrossEntropyLoss.html#torch.nn.CrossEntropyLoss>`_ combines ``nn.LogSoftmax`` and ``nn.NLLLoss``.
#
# We pass our model's output logits to ``nn.CrossEntropyLoss``, which will normalize the logits and compute the prediction error.

# Initialize the loss function
loss_fn = nn.CrossEntropyLoss()



#####################################
# Optimizer
# ~~~~~~~~~~~~~~~~~
#
# Optimization is the process of adjusting model parameters to reduce model error in each training step. **Optimization algorithms** define how this process is performed (in this example we use Stochastic Gradient Descent).
# All optimization logic is encapsulated in  the ``optimizer`` object. Here, we use the SGD optimizer; additionally, there are many `different optimizers <https://pytorch.org/docs/stable/optim.html>`_
# available in PyTorch such as ADAM and RMSProp, that work better for different kinds of models and data.
#
# We initialize the optimizer by registering the model's parameters that need to be trained, and passing in the learning rate hyperparameter.

optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

#####################################
# Inside the training loop, optimization happens in three steps:
#  * Call ``optimizer.zero_grad()`` to reset the gradients of model parameters. Gradients by default add up; to prevent double-counting, we explicitly zero them at each iteration.
#  * Backpropagate the prediction loss with a call to ``loss.backward()``. PyTorch deposits the gradients of the loss w.r.t. each parameter.
#  * Once we have our gradients, we call ``optimizer.step()`` to adjust the parameters by the gradients collected in the backward pass.


########################################
# .. _full-impl-label:
#
# Full Implementation
# -----------------------
# We define ``train_loop`` that loops over our optimization code, and ``test_loop`` that
# evaluates the model's performance against our test data.

def train_loop(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    for batch, (X, y) in enumerate(dataloader):
        # Compute prediction and loss
        pred = model(X)
        loss = loss_fn(pred, y)

        # Backpropagation
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch % 100 == 0:
            loss, current = loss.item(), batch * len(X)
            print(f"loss: {loss:>7f}  [{current:>5d}/{size:>5d}]")


def test_loop(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    test_loss, correct = 0, 0

    with torch.no_grad():
        for X, y in dataloader:
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()

    test_loss /= num_batches
    correct /= size
    print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")


########################################
for t in range(epochs):
    print(f"Epoch {t+1}\n-------------------------------")
    train_loop(train_dataloader, model, loss_fn, optimizer)
    test_loop(test_dataloader, model, loss_fn)
print("Done!")



#################################################################
# Further Reading
# -----------------------
# - `Loss Functions <https://pytorch.org/docs/stable/nn.html#loss-functions>`_
# - `torch.optim <https://pytorch.org/docs/stable/optim.html>`_
# - `Warmstart Training a Model <https://pytorch.org/tutorials/recipes/recipes/warmstarting_model_using_parameters_from_a_different_model.html>`_
#################################################################