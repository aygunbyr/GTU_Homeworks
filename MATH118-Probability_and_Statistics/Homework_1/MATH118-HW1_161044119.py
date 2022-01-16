#import csv file, read and insert into list
import csv
with open('owid-covid-data.csv', 'r') as infile:
    reader = csv.reader(infile)
    data = list(reader)

# open output file and write first line
outfile = open("output.csv", 'w')
outfile.write("Country,q#3,q#4,q#5_min,q#5_max,q#5_avg,q#5_var,q#6_min,q#6_max,q#6_avg,q#6_var,q#7_min,q#7_max,q#7_avg,q#7_var,q#8_min,q#8_max,q#8_avg,q#8_var,q#9_min,q#9_max,q#9_avg,q#9_var,q#10_min,q#10_max,q#10_avg,q#10_var,q#11,q#12_min,q#12_max,q#12_avg,q#12_var,q#13_min,q#13_max,q#13_avg,q#13_var,q#14,q#15,q#16,population,median_age,# of people aged 65 older,# of people aged 70 older,economic performance,death rates due to heart disease,diabetes prevalence,#of female smokers,#of male smokers,handwashing facilities,hospital beds per thousand people,life expectancy,human development index\n")


# Fill the country list
country_name = "location"
country_list = []
for i in data:
    if i[2] != country_name:
        country_name = i[2]
        country_list.append(country_name)


# Question 1, 2
q1 = len(country_list)
q2_date = "date"
q2_country = "location"
for i in data:
    if i[3] < q2_date:
        q2_date = i[3]
        q2_country = i[2]

# Question 3-17
# loop for each country
for i in country_list:
    country = i
    date = None
    total_cases = 0.0
    total_deaths = 0.0
    total_tests = 0.0
    total_vaccinations = 0.0
    vaccinated_one_dose = 0.0
    vaccinated_fully = 0.0
    population = 0.0
    median_age = 0.0
    number_of_65_older = 0.0
    number_of_70_older = 0.0
    # gdp per capita presents economic performance
    gdp_per_capita = 0.0
    # cardiovasc death rate presents death rates due to heart disease
    cardiovasc_death_rate = 0.0
    diabetes_prevalence = 0.0
    number_of_female_smokers = 0.0
    number_of_male_smokers = 0.0
    handwashing_facilities = 0.0
    hospital_beds_per_thousand = 0.0
    life_expectancy = 0.0
    human_development_index = 0.0

    # default values are zero
    q5_min = 0.0
    q5_max = 0.0
    q5_sum = 0.0
    q5_num = 0
    q5_mean = 0.0
    q5_var = 0.0

    q6_min = 0.0
    q6_max = 0.0
    q6_sum = 0.0
    q6_num = 0
    q6_mean = 0.0
    q6_var = 0.0

    q7_min = 0.0
    q7_max = 0.0
    q7_sum = 0.0
    q7_num = 0
    q7_mean = 0.0
    q7_var = 0.0

    q8_min = 0.0
    q8_max = 0.0
    q8_sum = 0.0
    q8_num = 0
    q8_mean = 0.0
    q8_var = 0.0

    q9_min = 0.0
    q9_max = 0.0
    q9_sum = 0.0
    q9_num = 0
    q9_mean = 0.0
    q9_var = 0.0

    q10_min = 0.0
    q10_max = 0.0
    q10_sum = 0.0
    q10_num = 0
    q10_mean = 0.0
    q10_var = 0.0

    q12_min = 0.0
    q12_max = 0.0
    q12_sum = 0.0
    q12_num = 0
    q12_mean = 0.0
    q12_var = 0.0

    q13_min = 0.0
    q13_max = 0.0
    q13_sum = 0.0
    q13_num = 0
    q13_mean = 0.0
    q13_var = 0.0

    # we picked an earlier date
    date = "01-01-2019"
    for i in data:
        if i[2] == country:
            if i[3] > date:
                # update values when it is not empty in csv 
                # total cases
                if i[4] != '':
                    total_cases = float(i[4])
                # total deaths
                if i[7] != '':
                    total_deaths = float(i[7])
                # calculating average, minimum and maximum values of reproduction_rate
                if i[16] != '':
                    if q5_min == 0.0:
                        q5_min = float(i[16])
                    if q5_max == 0.0:
                        q5_max = float(i[16])
                    if float(i[16]) < q5_min:
                        q5_min = float(i[16])
                    if float(i[16]) > q5_max:
                        q5_max = float(i[16])
                    q5_sum = q5_sum + float(i[16])
                    q5_num = q5_num + 1
                # calculating average, minimum and maximum values of icu_patients
                if i[17] != '':
                    if q6_min == 0.0:
                        q6_min = float(i[17])
                    if q6_max == 0.0:
                        q6_max = float(i[17])
                    if float(i[17]) < q6_min:
                        q6_min = float(i[17])
                    if float(i[17]) > q6_max:
                        q6_max = float(i[17])
                    q6_sum = q6_sum + float(i[17])
                    q6_num = q6_num + 1
                # calculating average, minimum and maximum values of hosp_patients
                if i[19] != '':
                    if q7_min == 0.0:
                        q7_min = float(i[19])
                    if q7_max == 0.0:
                        q7_max = float(i[19])
                    if float(i[19]) < q7_min:
                        q7_min = float(i[19])
                    if float(i[19]) > q7_max:
                        q7_max = float(i[19])
                    q7_sum = q7_sum + float(i[19])
                    q7_num = q7_num + 1
                # calculating average, minimum and maximum values of weekly_icu_admissions
                if i[21] != '':
                    if q8_min == 0.0:
                        q8_min = float(i[21])
                    if q8_max == 0.0:
                        q8_max = float(i[21])
                    if float(i[21]) < q8_min:
                        q8_min = float(i[21])
                    if float(i[21]) > q8_max:
                        q8_max = float(i[21])
                    q8_sum = q8_sum + float(i[21])
                    q8_num = q8_num + 1
                # calculating average, minimum and maximum values of weekly_hosp_admissions
                if i[23] != '':
                    if q9_min == 0.0:
                        q9_min = float(i[23])
                    if q9_max == 0.0:
                        q9_max = float(i[23])
                    if float(i[23]) < q9_min:
                        q9_min = float(i[23])
                    if float(i[23]) > q9_max:
                        q9_max = float(i[23])
                    q9_sum = q9_sum + float(i[23])
                    q9_num = q9_num + 1
                # calculating average, minimum and maximum values of new_tests
                if i[25] != '':
                    if q10_min == 0.0:
                        q10_min = float(i[25])
                    if q10_max == 0.0:
                        q10_max = float(i[25])
                    if float(i[25]) < q10_min:
                        q10_min = float(i[25])
                    if float(i[25]) > q10_max:
                        q10_max = float(i[25])
                    q10_sum = q10_sum + float(i[25])
                    q10_num = q10_num + 1
                # calculating average, minimum and maximum values of positive_rate
                if i[31] != '':
                    if q12_min == 0.0:
                        q12_min = float(i[31])
                    if q12_max == 0.0:
                        q12_max = float(i[31])
                    if float(i[31]) < q12_min:
                        q12_min = float(i[31])
                    if float(i[31]) > q12_max:
                        q12_max = float(i[31])
                    q12_sum = q12_sum + float(i[31])
                    q12_num = q12_num + 1
                # calculating average, minimum and maximum values of test_per_case
                if i[32] != '':
                    if q13_min == 0.0:
                        q13_min = float(i[32])
                    if q13_max == 0.0:
                        q13_max = float(i[32])
                    if float(i[32]) < q13_min:
                        q13_min = float(i[32])
                    if float(i[32]) > q13_max:
                        q13_max = float(i[32])
                    q13_sum = q13_sum + float(i[32])
                    q13_num = q13_num + 1            
                
                # total tests
                if i[26] != '':
                    total_tests = float(i[26])
                # total vaccinations
                if i[34] != '':
                    total_vaccinations = float(i[34])
                # # of people vaccinated one dose
                if i[35] != '':
                    vaccinated_one_dose = float(i[35])
                # # of people vaccinated two doses
                if i[36] != '':
                    vaccinated_fully = float(i[36])
                # population
                if i[44] != '':
                    population = float(i[44])
                # median age
                if i[46] != '':
                    median_age = float(i[46])
                # # of people older than age 65
                if i[47] != '':
                    number_of_65_older = float(i[47])
                # # of people older than age 70
                if i[48] != '':
                    number_of_70_older = float(i[48])
                # gdp per capita
                if i[49] != '':
                    gdp_per_capita = float(i[49])
                # cardiovascular death rate
                if i[51] != '':
                    cardiovasc_death_rate = float(i[51])
                # diabetes prevalence
                if i[52] != '':
                    diabetes_prevalence = float(i[52])
                # # of female smokers
                if i[53] != '':
                    number_of_female_smokers = float(i[53])
                # # of male smokers
                if i[54] != '':
                    number_of_male_smokers = float(i[54])
                # # of handwashing facilities
                if i[55] != '':
                    handwashing_facilities = float(i[55])
                # # of hospital beds per thousand people
                if i[56] != '':
                    hospital_beds_per_thousand = float(i[56])
                # life expectancy
                if i[57] != '':
                    life_expectancy = float(i[57])
                # human development index
                if i[58] != '':
                    human_development_index = float(i[58])

                # update date
                date = i[3]

    # Calculating means
    if q5_num > 0:
        q5_mean = q5_sum / q5_num
    if q6_num > 0:
        q6_mean = q6_sum / q6_num
    if q7_num > 0:
        q7_mean = q7_sum / q7_num
    if q8_num > 0:
        q8_mean = q8_sum / q8_num
    if q9_num > 0:
        q9_mean = q9_sum / q9_num
    if q10_num > 0:
        q10_mean = q10_sum / q10_num
    if q12_num > 0:
        q12_mean = q12_sum / q12_num
    if q13_num > 0:
        q13_mean = q13_sum / q13_num


    # Calculating variations
    for i in data:
        if i[2] == country:
            if i[16] != '':
                q5_var = q5_var + (float(i[16]) - q5_mean) * (float(i[16]) - q5_mean)
            if i[17] != '':
                q6_var = q6_var + (float(i[17]) - q6_mean) * (float(i[17]) - q6_mean)
            if i[19] != '':
                q7_var = q7_var + (float(i[19]) - q7_mean) * (float(i[19]) - q7_mean)
            if i[21] != '':
                q8_var = q8_var + (float(i[21]) - q8_mean) * (float(i[21]) - q8_mean)
            if i[23] != '':
                q9_var = q9_var + (float(i[23]) - q9_mean) * (float(i[23]) - q9_mean)
            if i[25] != '':
                q10_var = q10_var + (float(i[25]) - q10_mean) * (float(i[25]) - q10_mean)
            if i[31] != '':
                q12_var = q12_var + (float(i[31]) - q12_mean) * (float(i[31]) - q12_mean)
            if i[32] != '':
                q13_var = q13_var + (float(i[32]) - q13_mean) * (float(i[32]) - q13_mean)

    if q5_num > 0:
        q5_var = q5_var / q5_num
    if q6_num > 0:
        q6_var = q6_var / q6_num
    if q7_num > 0:
        q7_var = q7_var / q7_num
    if q8_num > 0:
        q8_var = q8_var / q8_num
    if q9_num > 0:
        q9_var = q9_var / q9_num
    if q10_num > 0:
        q10_var = q10_var / q10_num
    if q12_num > 0:
        q12_var = q12_var / q12_num
    if q13_num > 0:
        q13_var = q13_var / q13_num

    # write into output file
    # each line presents one country
    line = "{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}\n".format(country,  total_cases, total_deaths, q5_min, q5_max, q5_mean, q5_var, q6_min, q6_max, q6_mean, q6_var, q7_min, q7_max, q7_mean, q7_var, q8_min, q8_max, q8_mean, q8_var, q9_min, q9_max, q9_mean, q9_var, q10_min, q10_max, q10_mean, q10_var, total_tests, q12_min, q12_max, q12_mean, q12_var, q13_min, q13_max, q13_mean, q13_var, vaccinated_one_dose, vaccinated_fully, total_vaccinations, population, median_age, number_of_65_older, number_of_70_older, gdp_per_capita, cardiovasc_death_rate, diabetes_prevalence, number_of_female_smokers, number_of_male_smokers, handwashing_facilities, hospital_beds_per_thousand, life_expectancy, human_development_index)
    outfile.write(line);

