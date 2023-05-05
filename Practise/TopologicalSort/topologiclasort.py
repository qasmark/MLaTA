def read_input():
    n = int(input())
    doctors = [{'needed': list(map(int, input().split()[1:])), 'visited': False} for _ in range(n)]
    return doctors

def can_obtain_all_certificates(doctors):
    order = []
    while True:
        doctor_idx = -1
        for i, doctor in enumerate(doctors):
            if not doctor['visited'] and all(doctors[x-1]['visited'] for x in doctor['needed']):
                doctor_idx = i
                break
        if doctor_idx == -1: 
            return False
        order.append(doctor_idx+1)
        doctors[doctor_idx]['visited'] = True
        if all(doctor['visited'] for doctor in doctors):
            return order

def main():
    doctors = read_input()
    order = can_obtain_all_certificates(doctors)
    if order:
        print('YES')
        print('\n'.join(map(str, order)))
    else:
        print('NO')

if __name__ == "__main__":
    main()
# Версия питона 3.10.4
