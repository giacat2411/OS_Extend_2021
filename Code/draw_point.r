setwd(getwd())
test = read.csv("3000.csv", header = FALSE)
result = read.csv("result.csv", header = FALSE)

plot(test, xlab = "x", ylab = "y", main = "Tap diem va bao loi", col = "red")

ch <- chull(result)
kq <- result[c(ch, ch[1]), ]  # closed polygon

lines(kq, col="blue")
