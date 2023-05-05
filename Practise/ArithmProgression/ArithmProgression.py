with open('in4.txt', 'r') as f_in:
    num_blocks = int(f_in.readline())

    for block in range(num_blocks):
        n = int(f_in.readline())
        nums = list(map(int, f_in.readline().split()))
        if (len(nums) == 2):
            print('Yes')
            continue
        if (len(nums) < 3):
            print('No')
            continue
        nums.sort()

        step = None
        for i in range(n - 1):
            if step is None and nums[i] != nums[i+1]:
                step = nums[i+1] - nums[i]
            
            if step is not None and nums[i+1] - nums[i] != step:
                print('No')
                break
        else:
            print('Yes')
            continue
