########################################################################
# Loading libraries
########################################################################
library(Sleuth2)
library(fitdistrplus)
library(logspline)

########################################################################
# Loading dataset and splitting by the Treatment variable
########################################################################

ds = case0101
ds.split = split(ds, ds$Treatment)
ds.intrinsic = ds.split$Intrinsic$Score
ds.extrinsic = ds.split$Extrinsic$Score

########################################################################
########################################################################
########################### INTRINSIC VECTOR ###########################
########################################################################
########################################################################


########################################################################
# Summarizing Score 
########################################################################

summary(ds.intrinsic)
var(ds.intrinsic)

########################################################################
# Now let have a look at densities and empirical distribution functions.
########################################################################

hist(ds.intrinsic, freq=FALSE, breaks = 6)
plot(ecdf(ds.intrinsic))


########################################################################
# We can see that the distribution looks much like a Gaussian.
# But let's check our hypothesis using the descdist function 
# from the fitdistrplus package.
########################################################################

descdist(ds.intrinsic)

########################################################################
# From the plot we see that the skewness and kurtosis params of 
# our vector are almost the same as for the Gaussian distribution.
# Let's try to fit several known distributions: norm, exp, unif.
########################################################################

fit.intrinsic.norm = fitdist(ds.intrinsic, "norm")
fit.intrinsic.exp = fitdist(ds.intrinsic, "exp")
fit.intrinsic.unif = fitdist(ds.intrinsic, "unif")

########################################################################
# Now we'll have a look at the plots and at the Akaike 
# information criterion for choosing the best distribution.
########################################################################

plot(fit.intrinsic.norm)
fit.intrinsic.norm$aic

plot(fit.intrinsic.exp)
fit.intrinsic.exp$aic

plot(fit.intrinsic.unif)
fit.intrinsic.unif$aic

########################################################################
# We see that the lowest AIC is for the normal distribution.
# Moreover, visually it approximates our data quiet well.
# 
# So, our choice for the intrinsic dataset is a normal distribution.
# With parameters:
########################################################################

fit.intrinsic.norm$estimate
fit.intrinsic.exp$estimate
fit.intrinsic.unif$estimate

mu.intrinsic = fit.intrinsic.norm$estimate['mean']
sigma.intrinsic = fit.intrinsic.norm$estimate['sd']

########################################################################
# Now let's plot all the distributions on the same plot.
########################################################################

x.intrinsic.min = min(ds.intrinsic)
x.intrinsic.max = max(ds.intrinsic)
x.intrinsic = seq(x.intrinsic.min, x.intrinsic.max, length = 1000)

y.intrinsic.norm = dnorm(x.intrinsic, mean = mu.intrinsic, sd = sigma.intrinsic)
y.intrinsic.exp = dexp(x.intrinsic, rate = fit.intrinsic.exp$estimate['rate'])
y.intrinsic.unif = dunif(x.intrinsic, min = fit.intrinsic.unif$estimate['min'], max = fit.intrinsic.unif$estimate['max'])

hist(ds.intrinsic, breaks = 6, freq = FALSE)
lines(x = x.intrinsic, y = y.intrinsic.norm, col = 'red')
lines(x = x.intrinsic, y = y.intrinsic.exp, col = 'blue')
lines(x = x.intrinsic, y = y.intrinsic.unif, col = 'green')

########################################################################
# Now let's compare histograms of a generated dataset and ours.
########################################################################

sample.intrinsic.norm = rnorm(100, mean = mu.intrinsic, sd = sigma.intrinsic)

par(mfrow = c(1, 2))
hist(ds.intrinsic, breaks = 6, freq = FALSE, main = "Intrinsic dataset")
hist(sample.intrinsic.norm, breaks = 6, freq = FALSE, main = "Generated dataset")

########################################################################
# On the right side we see that the generated distribution has both 
# the same mean and sd values. Because we generated 1000 samples 
# we see that the right plot is more like a Gaussian.
########################################################################

########################################################################
# Let's calculate the 95% confidence interval.
########################################################################

siglevel = 0.05

conf.int.intrinsic = t.test(ds.intrinsic, conf.level = 1 - siglevel)$conf.int

########################################################################
# Let's test the 5% hypothesis that a mean value lays in the 
# confidence interval with a probability of 95%.
########################################################################

par(mfrow = c(1, 1))

testnbr = 100
missed = 0

plot(c(1, testnbr), c(mu.intrinsic, mu.intrinsic), type = 'l', lty = 'dashed', xlab = 'Attempt', ylab = '')

for (i in 1:testnbr) {
    spl = rnorm(5, mean = mu.intrinsic, sd = sigma.intrinsic)
    confint = t.test(spl, conf.level = 1 - siglevel)$conf.int

    if (mu.intrinsic >= confint[1]  &  mu.intrinsic <= confint[2]) {
    	segcol = 'blue'
    } else { 
    	segcol = 'orange'
        missed = missed + 1
    }

    segments(x0 = i, y0 = confint[1], x1 = i, y1 = confint[2], col = segcol)
}

# Check how many intervals are out of our confidence interval
missed / testnbr

########################################################################
# Let's check if the mean value of the intrinsic dataset is equals 
# to the value of K (K = 28). We'll use the 5% significance level
# interval. 
########################################################################

t.test(ds.intrinsic, mu=28)

########################################################################
# From the output we see that the p-value is 5.857e-09, which is less
# than 0.05. That means that we can reject the null-hypothesis, that is,
# the mean value of the extrinsic data set is not equal to the value of
# K, K = 28.
########################################################################

########################################################################
########################################################################
########################### EXTRINSIC VECTOR ###########################
########################################################################
########################################################################


########################################################################
# Summarizing Score 
########################################################################

summary(ds.extrinsic)
var(ds.extrinsic)

########################################################################
# Now let have a look at densities and empirical distribution functions.
########################################################################

hist(ds.extrinsic, freq=FALSE, breaks = 6)
plot(ecdf(ds.extrinsic))

########################################################################
# We can see that the distribution looks much like a Gaussian.
# But let's check our hypothesis using the descdist function 
# from the fitdistrplus package.
########################################################################

descdist(ds.extrinsic)

########################################################################
# From the plot we see that the skewness and kurtosis params of 
# our vector are almost the same as for the Gaussian distribution.
# Let's try to fit several known distributions: norm, exp, unif.
########################################################################

fit.extrinsic.norm = fitdist(ds.extrinsic, "norm")
fit.extrinsic.exp = fitdist(ds.extrinsic, "exp")
fit.extrinsic.unif = fitdist(ds.extrinsic, "unif")

########################################################################
# Now we'll have a look at the plots and at the Akaike 
# information criterion for choosing the best distribution.
########################################################################

plot(fit.extrinsic.norm)
fit.extrinsic.norm$aic

plot(fit.extrinsic.exp)
fit.extrinsic.exp$aic

plot(fit.extrinsic.unif)
fit.extrinsic.unif$aic

########################################################################
# We see that the lowest AIC is for the normal distribution.
# Moreover, visually it approximates our data quiet well.
# 
# So, our choice for the extrinsic dataset is a normal distribution.
# With parameters:
########################################################################

fit.extrinsic.norm$estimate
fit.extrinsic.exp$estimate
fit.extrinsic.unif$estimate

mu.extrinsic = fit.extrinsic.norm$estimate['mean']
sigma.extrinsic = fit.extrinsic.norm$estimate['sd']

########################################################################
# Now let's plot all the distributions on the same plot.
########################################################################

x.extrinsic.min = min(ds.extrinsic)
x.extrinsic.max = max(ds.extrinsic)
x.extrinsic = seq(x.extrinsic.min, x.extrinsic.max, length = 1000)

y.extrinsic.norm = dnorm(x.extrinsic, mean = mu.extrinsic, sd = sigma.extrinsic)
y.extrinsic.exp = dexp(x.extrinsic, rate = fit.extrinsic.exp$estimate['rate'])
y.extrinsic.unif = dunif(x.extrinsic, min = fit.extrinsic.unif$estimate['min'], max = fit.extrinsic.unif$estimate['max'])

hist(ds.extrinsic, breaks = 6, freq = FALSE)
lines(x = x.extrinsic, y = y.extrinsic.norm, col = 'red')
lines(x = x.extrinsic, y = y.extrinsic.exp, col = 'blue')
lines(x = x.extrinsic, y = y.extrinsic.unif, col = 'green')

########################################################################
# Now let's compare histograms of a generated dataset and ours.
########################################################################

sample.extrinsic.norm = rnorm(100, mean = mu.extrinsic, sd = sigma.extrinsic)

par(mfrow = c(1, 2))
hist(ds.extrinsic, breaks = 6, freq = FALSE, main = "Extrinsic dataset")
hist(sample.extrinsic.norm, breaks = 6, freq = FALSE, main = "Generated dataset")

########################################################################
# On the right side we see that the generated distribution has both 
# the same mean and sd values. Because we generated 1000 samples 
# we see that the right plot is more like a Gaussian.
########################################################################

########################################################################
# Let's calculate the 95% confidence interval.
########################################################################

siglevel = 0.05

conf.int.extrinsic = t.test(ds.extrinsic, conf.level = 1 - siglevel)$conf.int

########################################################################
# Let's test the 5% hypothesis that a mean value lays in the 
# confidence interval with a probability of 95%.
########################################################################

par(mfrow = c(1, 1))

testnbr = 100
missed = 0

plot(c(1, testnbr), c(mu.extrinsic, mu.extrinsic), type = 'l', lty = 'dashed', xlab = 'Attempt', ylab = '')

for (i in 1:testnbr) {
    spl = rnorm(5, mean = mu.extrinsic, sd = sigma.extrinsic)
    confint = t.test(spl, conf.level = 1 - siglevel)$conf.int

    if (mu.extrinsic >= confint[1]  &  mu.extrinsic <= confint[2]) {
    	segcol = 'blue'
    } else { 
    	segcol = 'orange'
        missed = missed + 1
    }

    segments(x0 = i, y0 = confint[1], x1 = i, y1 = confint[2], col = segcol)
}

# Check how many intervals are out of our confidence interval
missed / testnbr

########################################################################
# Let's check if the mean value of the extrinsic dataset is equals 
# to the value of K (K = 28). We'll use the 5% significance level
# interval. 
########################################################################

t.test(ds.extrinsic, mu=28)

########################################################################
# From the output we see that the p-value is 1.491e-10, which is less
# than 0.05. That means that we can reject the null-hypothesis, that is,
# the mean value of the intrinsic data set is not equal to the value of
# K, K = 28.
########################################################################

########################################################################
########################################################################
################### COMPARING TWO DISTRIBUTIONS ########################
########################################################################
########################################################################

########################################################################
# First of all, before using the two sample t-test, we should 
# evaluate a Fisher’s F-test and verify a homogeneity of variances.
########################################################################

var.test(ds.intrinsic, ds.extrinsic)

########################################################################
# We see that the p-value of 0.4289 is greater than 0.05, thus
# variances are homogeneous.
########################################################################
# So, the variances are homogeneous, our datasets follow the Gaussian
# distribution, therefore, we can perform a t-test.
#
# Let's compare if our distributions have the same mean values. 
# We'll use again the 95% confidence interval.
#
# H0 - the mean values are the same on the 95% interval.
# HA - they are different.
########################################################################

t.test(ds.intrinsic, ds.extrinsic, var.equal=TRUE)

########################################################################
# We have the p-value of 0.005366, which is less then 0.05. So, the 
# H0 can be rejected, mean values of our distributions are different.
########################################################################

########################################################################
# Let's now draw just for fun our 95% confidence intervals.
########################################################################

plot(c(conf.int.intrinsic[1], conf.int.intrinsic[2]), c(1, 1), type = 'l', lty = 'solid', xlab = 'Confidence intervals', ylab = '', xlim=c(12, 23), ylim=c(0.5, 2), col = 'blue')
points(x = mu.intrinsic, y = 1, pch = 5, col = 'blue')
segments(x0 = conf.int.intrinsic[1], x1 = conf.int.intrinsic[1], y0 = 0, y1 = 1, lty = 'dashed')
segments(x0 = conf.int.intrinsic[2], x1 = conf.int.intrinsic[2], y0 = 0, y1 = 1, lty = 'dashed')

segments(x0 = conf.int.extrinsic[1], y0 = 1.5, x1 = conf.int.extrinsic[2], y1 = 1.5, col = 'red')
points(x = mu.extrinsic, y = 1.5, pch = 5, col = 'red')
segments(x0 = conf.int.extrinsic[1], x1 = conf.int.extrinsic[1], y0 = 0, y1 = 1.5, lty = 'dashed')
segments(x0 = conf.int.extrinsic[2], x1 = conf.int.extrinsic[2], y0 = 0, y1 = 1.5, lty = 'dashed')

########################################################################
# So, we see that these intervals do not even have intersections. 
# Let's plot two fitted distributions.  
########################################################################

plot(x = x.intrinsic, y = y.intrinsic.norm, col = 'blue', type = 'l', lty = 'solid', xlim=c(5, 30))
lines(x = x.extrinsic, y = y.extrinsic.norm, col = 'red')

########################################################################
# We can clearly see that the mean values of our samples are 
# different, which only confirms our assumtions about rejecting the 
# null hypothesis.
########################################################################