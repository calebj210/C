### Longest Collatz Sequence Finder

function nxt(n)
    if n%2 == 0
        return n/2
    else
        return 3n+1
    end
end

function findMax(mx)
    # Initialize needed variables
    lngth = 0
    n = 1
    mxLngth = 0
    mxStart = 1
    
    for i∈1:mx-1
        # Reset start and lngth
        n = i
        lngth = 0

        # Generate the Collatz sequence
        while n != 1
            n = nxt(n)
            lngth += 1
        end

        # Store largest sequence length and start
        if lngth > mxLngth
            mxLngth = lngth
            mxStart = i
        end
    end

    display(mxStart)
    display(mxLngth)

    return mxStart
end

findMax(1000000)
