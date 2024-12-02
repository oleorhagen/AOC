
function abs(a) {
    if (a < 0)  {
        return -a
    }
    return a
}

{
    left[NR] = $1;
    right[NR] = $2
}

END {
    n = asort(left)
    asort(right)
    for (i = 1; i<= n; i++) {
        printf("Mid sum: %d\n", abs( left[i] - right[i] ))
        sum += abs( left[i] - right[i] )
    }
    print sum
}

