#==================================================================
#             Media and Cognition
#             Week 13  Feature Extraction and Dimension Reduction
#             classifier.py - classifiers: LDF, QDF, MQDF
#             Tsinghua University
#             (C) Copyright 2021
#==================================================================

import math
import pprint

import numpy as np
import numpy.matlib
from numpy import linalg


def print_cov_matrix(cov_matrix):
    """ Print each covariance matrix for each class
    """
    print('Covariance matrix for each class:')
    num_class = len(cov_matrix)
    for i in range(num_class):
        print('Class %d:' % i)
        pprint.pprint(cov_matrix[i])


def build_QDF_model(num_class, x_train, y_train):
    """ Cacualte prior prob., means and covariance matrix for each class
    """
    data = []
    train_count = len(x_train)
    for i in range(num_class):
        data.append(list())

    # Note: class indexes must be 0,1,2,... staring with 0
    for i in range(train_count):
        class_index = int(y_train[i])
        data[class_index].append(x_train[i])

    mean = []
    cov_matrix = []
    prior = []
    # pdb.set_trace()
    for i in range(num_class):
        data[i] = np.matrix(data[i], dtype=np.float64)
        mean.append(data[i].mean(0).T)
        # np.cov treat each row as one feature, so data[i].T has to be transposed
        cov_matrix.append(np.matrix(np.cov(data[i].T)) + 1e-8 * np.eye(x_train.shape[1]))
        prior.append(len(data[i]) * 1.0 / train_count)

    return prior, mean, cov_matrix


def QDF_predict(x_test, num_class, prior, mean, cov_matrix):
    """ Predict class labels
    Find the class lable that maximize the prob
    """
    inverse_cov = []
    log_det_cov = []
    for i in range(num_class):
        det = np.linalg.det(cov_matrix[i])
        if det <= 0:
            d, m = cov_matrix[i].shape
            gamma = 0.5
            cov = cov_matrix[i] + gamma * np.eye(d)  # add a regularizer
            inverse_cov.append(cov.getI())
            det = np.linalg.det(cov)
        else:
            inverse_cov.append(cov_matrix[i].getI())

        log_det_cov.append(math.log(det))

    predicted_labels = []
    for row in x_test:
        x = np.matrix(row, np.float64).T
        max_posteriori = -float('inf')
        prediction = -1
        for i in range(num_class):
            diff = x - mean[i]
            p = 2 * math.log(prior[i])  # we do not ignore priors here
            p = p - (diff.T * inverse_cov[i] * diff)[0, 0] - log_det_cov[i]
            if p > max_posteriori:
                max_posteriori = p
                prediction = i

        predicted_labels.append(prediction)

    return predicted_labels


def build_LDF_model(num_class, x_train, y_train):
    """ LDF model
    First call QDF model to caculate the mean, cov_matirx
    """
    prior, mean, cov_matrix = build_QDF_model(num_class, x_train, y_train)
    # print_cov_matrix(cov_matrix)

    # cacualte the shared covariance matirx
    avg_cov = np.matlib.zeros(cov_matrix[0].shape)
    for i in range(num_class):
        avg_cov += (prior[i] * cov_matrix[i])

    inverse_cov = avg_cov.getI()  # get the inverse covariance matrix

    num_feature = x_train.shape[1]
    # each column for weight[i]
    weight = np.matrix([0] * num_feature).T
    w0 = []
    for i in range(num_class):
        wi = 2 * inverse_cov.T * mean[i]
        weight = np.hstack((weight, wi))

        wi0 = 2 * math.log(prior[i]) - (mean[i].T * inverse_cov * mean[i])[0, 0]
        w0.append(wi0)

    return inverse_cov, weight[:, 1:], w0


def LDF_predict(x_test, num_class, inverse_cov, weight, w0):
    predicted_labels = []
    for row in x_test:
        x = np.matrix(row, np.float64).T
        max_posteriori = -float('inf')
        prediction = -1
        for i in range(num_class):
            p = (-1 * (x.T * inverse_cov * x) + weight[:, i].T * x + w0[i])[0, 0]
            # p = (weight[:, i].T * x + w0[i])[0,0]
            if p > max_posteriori:
                max_posteriori = p
                prediction = i

        predicted_labels.append(prediction)

    return predicted_labels


def build_MQDF_model(num_class, x_train, y_train, k, delta0):
    """ MQDF model
    @k and @delta are hyper-parameters

    Note: There are three possible ways to set @delta:
    1) @delta is a hyper-parameter, set by cross validation
    2) @delta can be estimated via ML estimation, in which case, this delta
        is no longer a hyper-parameter
    3) @delta can be set close to $\sigma_{i,k}$ or $\sigma_{i,k+1}$, in which case,
        this delta is also not a hyper-parameter
    """
    d = len(x_train[0])  # number of features
    assert (k < d and k > 0)

    prior, mean, cov_matrix = build_QDF_model(num_class, x_train, y_train)

    eigenvalue = []  # store the first largest k eigenvalues of each class
    eigenvector = []  # the first largest k eigenvectors, column-wise of each class
    delta = [0] * num_class  # deltas for each class
    for i in range(num_class):
        cov = cov_matrix[i]
        eig_values, eig_vectors = linalg.eigh(cov)
        # sort the eigvalues
        idx = eig_values.argsort()
        idx = idx[::-1]  # reverse the array
        eig_values = eig_values[idx]
        eig_vectors = eig_vectors[:, idx]

        eigenvector.append(eig_vectors[:, 0:k])
        eigenvalue.append(eig_values[:k])

        # delta via ML estimation
        # delta[i] = (cov.trace() - sum(eigenvalue[i])) * 1.0 / (d-k)

        # delta close to $\sigma_{i,k-1}$ or $\sigma_{i,k}$
        # delta[i] = (eig_values[k-1] + eig_values[k])/2
        # print 'Suggestd delta[%d]: %f' % (i, (eig_values[k] + eig_values[k+1])/2)

        # delta as the mean of minor values
        delta[i] = sum(eig_values[k:]) / len(eig_values[k:])

        if delta[i] < 0:
            delta[i] = 1e-15

    # delta = [delta0] * num_class
    return prior, mean, eigenvalue, eigenvector, delta


def MQDF_predict(x_test, num_class, k, mean, eigenvalue, eigenvector, delta):
    """ MQDF predict
    """
    d = len(x_test[0])
    y_pred = []
    for row in x_test:
        x = np.matrix(row, np.float64).T
        max_posteriori = -float('inf')
        prediction = -1
        for i in range(num_class):
            dis = np.linalg.norm(x.reshape((d,)) - mean[i].reshape((d,))) ** 2  # 2-norm
            # Mahalanobis distance
            ma_dis = [0] * k
            for j in range(k):
                ma_dis[j] = (((x - mean[i]).T * eigenvector[i][:, j])[0, 0]) ** 2

            p = 0
            for j in range(k):
                p += (ma_dis[j] * 1.0 / eigenvalue[i][j])

            p += ((dis - sum(ma_dis)) / delta[i])

            for j in range(k):
                p += math.log(eigenvalue[i][j])

            p += ((d - k) * math.log(delta[i]))
            p = -p

            if p > max_posteriori:
                max_posteriori = p
                prediction = i

        y_pred.append(prediction)

    return y_pred
