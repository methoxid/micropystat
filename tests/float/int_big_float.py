# test bignum operation with float/complex

i = 1 << 65

# this should convert to float
print("%.5g" % (i / 5))

# these should delegate to float
print("%.5g" % (i * 1.2))
print("%.5g" % (i / 1.2))

# this should delegate to complex
print("%.5g" % (i * 1.2j).imag)
