# 1. digit count
# conditions validating the size of a ccNum in terms of digits count
ccDigCount = 0

while ccDigCount < 13 or ccDigCount > 16:
    # 4539677908016808  # int(input("Enter CC number: "))
    ccNum = 4539677908016808
    copyOfCCNum = ccNum
    ccDigCount = len(str(copyOfCCNum))

# 2. Lun's algorithm

# copy cc number into a list
ccNumList = [int(x) for x in str(copyOfCCNum)]
dubed, summ, sumDubed = 0, 0, 0

# create a reverse of the list
reverseCC = ccNumList
reverseCC.reverse()

# syntactical validation of cc number (Lun's algo)
mults = 0
sumofProdDig = 0
x = []
sumOfOthers = 0
for i in range(1, len(reverseCC), 2):
    mults = reverseCC[i] * 2
    x = [int(k) for k in str(mults)]
    for j in range(0, len(x)):
        sumofProdDig = sumofProdDig + x[j]
sumOfOthers = sumOfOthers + sumofProdDig
for i in range(0, len(ccNumList), 2):
    sumOfOthers = sumOfOthers + ccNumList[i]

totalMod10 = sumOfOthers % 10
if totalMod10 == 0:
    dig1 = int(str(copyOfCCNum)[:1])
    dig2 = int(str(copyOfCCNum)[:2])
    if ccDigCount == 15 and dig2 == 34 or dig2 == 37:
        print("AMEX")
        exit()
    elif ccDigCount == 16 and dig2 > 50 and dig2 < 56:
        print("MASTERCARD")
        exit()
    elif ccDigCount > 12 and ccDigCount < 17 and dig1 == 4:
        print("VISA")
else:
    print("INVALID")
