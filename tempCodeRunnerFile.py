import sys
import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def extract_factors(n, factor):
    count = 0
    while n % factor == 0:
        count += 1
        n = n // factor
    return count, n

def prime_factors(n):
    factors = {}
    while n % 2 == 0:
        factors[2] = factors.get(2, 0) + 1
        n = n // 2
    i = 3
    while i * i <= n:
        while n % i == 0:
            factors[i] = factors.get(i, 0) + 1
            n = n // i
        i += 2
    if n > 1:
        factors[n] = 1
    return factors

def euler_phi(n):
    if n == 1:
        return 1
    factors = prime_factors(n)
    result = 1
    for p, exp in factors.items():
        result *= (p ** exp - p ** (exp - 1))
    return result

def multiplicative_order(n):
    if n == 1:
        return 1
    if math.gcd(10, n) != 1:
        return -1  # Not coprime
    phi = euler_phi(n)
    factors = prime_factors(phi)
    order = phi
    for p in factors:
        while order % p == 0:
            if pow(10, order // p, n) == 1:
                order = order // p
            else:
                break
    current = order
    for p in factors:
        while current % p == 0:
            if pow(10, current // p, n) == 1:
                current = current // p
            else:
                break
    return current

def solve():
    input = sys.stdin.read().split()
    idx = 0
    T = int(input[idx])
    idx += 1
    for _ in range(T):
        P = int(input[idx])
        Q = int(input[idx+1])
        s = int(input[idx+2])
        t = int(input[idx+3])
        idx +=4
        
        g = gcd(P, Q)
        P = P // g
        Q_orig = Q // g
        
        a, Q_remaining = extract_factors(Q_orig, 2)
        b, Q_remaining = extract_factors(Q_remaining, 5)
        L = max(a, b)
        Q_new = Q_remaining
        
        if Q_new == 1:
            pre_digits = []
            current_p = P % Q_orig
            for _ in range(L):
                current_p *= 10
                digit = current_p // Q_orig
                pre_digits.append(digit)
                current_p = current_p % Q_orig
            start = max(s, 1)
            end = min(t, L)
            sum_total = 0
            if start <= end and L > 0:
                sum_total += sum(pre_digits[start-1 : end])
            sum_total %= Q_orig
            print(sum_total)
        else:
            C = multiplicative_order(Q_new)
            if C == -1:
                print(0)
                continue
            
            cycle_digits = []
            current_p = (P * pow(10, L, Q_orig)) % Q_new
            for _ in range(C):
                current_p *= 10
                digit = current_p // Q_new
                cycle_digits.append(digit)
                current_p = current_p % Q_new
            sum_cycle = sum(cycle_digits)
            prefix_sum = [0] * (C + 1)
            for i in range(C):
                prefix_sum[i+1] = prefix_sum[i] + cycle_digits[i]
            
            sum_total = 0
            
            pre_digits = []
            current_p = P % Q_orig
            for _ in range(L):
                current_p *= 10
                digit = current_p // Q_orig
                pre_digits.append(digit)
                current_p = current_p % Q_orig
            start_pre = max(s, 1)
            end_pre = min(t, L)
            if start_pre <= end_pre:
                sum_total += sum(pre_digits[start_pre-1 : end_pre])
            
            start_cycle = max(s, L + 1)
            end_cycle = t
            if start_cycle > end_cycle:
                sum_total %= Q_orig
                print(sum_total)
                continue
            
            start_in_cycle = start_cycle - (L + 1)
            end_in_cycle = end_cycle - (L + 1)
            total_digits = end_in_cycle - start_in_cycle + 1
            if total_digits <= 0:
                sum_total %= Q_orig
                print(sum_total)
                continue
            
            start_pos = start_in_cycle % C
            full_cycles = total_digits // C
            remainder = total_digits % C
            
            sum_part = full_cycles * sum_cycle
            if remainder > 0:
                end_pos = start_pos + remainder - 1
                if end_pos < C:
                    sum_remainder = prefix_sum[end_pos + 1] - prefix_sum[start_pos]
                else:
                    sum_remainder = (prefix_sum[C] - prefix_sum[start_pos]) + (prefix_sum[end_pos - C + 1])
                sum_part += sum_remainder
            sum_total += sum_part
            sum_total %= Q_orig
            print(sum_total)

if __name__ == '__main__':
    sys.stdin = open('frac.inp', 'r')
    sys.stdout = open('frac.out', 'w')
    solve()