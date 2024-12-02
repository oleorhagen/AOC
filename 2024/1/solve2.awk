
# Similarity score calculation

function abs(a) {
    if (a < 0)  {
        return -a
    }
    return a
}

{
    # Collect the left list
    left[NR] += $1

    # Count the occurences of each number in the right list
    right[$2] += 1
}

END {
    # Loop through the left list, and multiply and sum equal nrs
    for (i=1; i<=NR; i++) {
        # print left[i]
        sum += left[i] * right[left[i]]
    }
    print sum
}

