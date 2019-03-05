# -*- coding: utf-8 -*-

import random
import copy
TRACK_MAX_COUNT = 100                 #磁道的总数
TRACK_REQUEST_COUNT = 10              #请求访问的磁道数量
TRACK_START = 50
SCAN_DIRECTION = 1                    # 1表示向磁道号增加的方向扫描，0表示向磁道号减小的方向
N_STEPSCAN = 4                        # 表示请求队列被划分为长度为 N 的子队列
 
def FCFS(track_request):
    queue_FCFS = track_request.copy()
    queue_FCFS.insert(0,TRACK_START)
    return queue_FCFS

def findNearest(current,track_request,visited):
    minDis = TRACK_MAX_COUNT
    minIndex = -1
    for i in range(len(track_request)):
        if visited[i] == False:
            dis = abs( current - track_request[i])
            if dis < minDis:
                minDis = dis
                minIndex = i
    visited[minIndex] = True
    return minIndex, minDis
 
def SSTF(track_request):
    visited = [False] * TRACK_REQUEST_COUNT
    queue_FCFS = []
    current = TRACK_START                               #起始的磁道
    for i in range(len(track_request)+1):
        index, dis = findNearest(current, track_request, visited)
        queue_FCFS.append(current)
        current = track_request[index]
    return queue_FCFS
 
    queue_SCAN.append(TRACK_START)
    current = TRACK_START
def SCAN(track_request):
    global SCAN_DIRECTION
    queue_SCAN = []
 
    track_request_copy = copy.deepcopy(track_request)
    track_request_copy.sort()
    while track_request_copy.__len__() != 0:
        if SCAN_DIRECTION == 1:
            for track in track_request_copy.copy():
                if TRACK_START <= track:
                    queue_SCAN.append(track)
                    track_request_copy.remove(track)
            SCAN_DIRECTION = 0
 
        if SCAN_DIRECTION == 0:
            track_request_copy.reverse()
            for track in track_request_copy.copy():
                if TRACK_START >= track:
                    queue_SCAN.append(track)
                    current = track
                    track_request_copy.remove(track)
            SCAN_DIRECTION = 1
    return queue_SCAN

def CSCAN(track_request):
    global SCAN_DIRECTION
    queue_CSCAN = []
    queue_CSCAN.append(TRACK_START)
    track_request_copy = copy.deepcopy(track_request)
    track_request_copy.sort()
    i = 0
    is_find = False
 
    if SCAN_DIRECTION ==1:
        while i < track_request_copy.__len__():
            if (TRACK_START <= track_request_copy[i] ) & (is_find == False):
                index = i
                i = 0
                is_find = True
            if is_find == True:
                queue_CSCAN.append(track_request_copy[index % TRACK_REQUEST_COUNT])
                index += 1
            i +=1
 
    if SCAN_DIRECTION ==0:
        track_request_copy.reverse()
        while i < track_request_copy.__len__():
            if (TRACK_START >= track_request_copy[i] ) & (is_find == False):
                index = i
                i = 0
                is_find = True
            if is_find == True:
                queue_CSCAN.append(track_request_copy[index % TRACK_REQUEST_COUNT])
                index += 1
                current = track_request_copy[index % TRACK_REQUEST_COUNT]
            i +=1
 
    return queue_CSCAN
 
def caculate(queue):
    print('访问的磁道序列为: ',end = '')
    print(queue)
    sum_gap = sum([(abs(queue[i] - queue[i - 1])) for i in range(1, len(queue))])
    print('移动的磁道数为：%d' % sum_gap)
    print('平均移动的磁道数为：%.2f' % (sum_gap/TRACK_REQUEST_COUNT))
    print("")
 
if __name__ == '__main__':
    track_request = [None] * TRACK_REQUEST_COUNT
    for i in range(TRACK_REQUEST_COUNT):
        track_request[i] = random.randint(0, TRACK_MAX_COUNT)
 
    print('每次生成的磁道序列是随机的，对于不同的序列算法的算法的性能是不一样的，'
          '通过多次比较观察结果，SSTF是算法中移动的磁道数最少的') 
    print("TRACK SEQUECE:    ")
    print(track_request)
    print('')
 
    print("FCFS:    ")
    caculate(FCFS(track_request))
 
    print("SSTF:    ")
    caculate(SSTF(track_request))
 
    print("SCAN:    ")
    caculate(SCAN(track_request))
 
    print("CSCAN:   ")
    caculate(CSCAN(track_request))
 

 

