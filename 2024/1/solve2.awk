
# Similarity score calculation

function abs(a) {
    if (a < 0)  {
        return -a
    }
    return a
}

{
    # Collect the loc_id list
    loc_id[NR] += $1

    # Count the occurences of each number in the right list
    count[$2] += 1
}

END {
    # Loop through the loc_id list, and multiply and sum equal nrs
    for (i=1; i<=NR; i++) {
        # print loc_id[i]
        sum += loc_id[i] * count[loc_id[i]]
    }
    print sum
}

