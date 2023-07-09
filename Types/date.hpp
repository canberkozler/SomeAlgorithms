#pragma once
#include <ostream>
#include <istream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <random>

std::mt19937& gen_eng(){
		static std::mt19937 eng{ std::random_device{}() };
		return eng;
};
class Irand {
public:
	Irand() = default;
	Irand(std::size_t min, std::size_t max) : m_dist{ min, max } {}
	std::size_t operator()(){
		return m_dist(gen_eng());
	}
private:
	std::uniform_int_distribution<std::size_t> m_dist;
};

class Date{
public:
    Date() = default;
    Date(std::size_t d_, std::size_t m_,std::size_t y_){
        set(d_, m_, y_);
    }

    Date(const char *p){
        set(atoi(p), atoi(p + 3), atoi(p + 6));
    }

    // Get Functions
	constexpr std::size_t get_month() const { return month; };
	constexpr std::size_t get_year() const { return year; };
	constexpr std::size_t get_day() const { return day; };

	constexpr std::size_t get_week()const{
		// array with leading number of days values 
		const std::size_t t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

		// if month is less than 3 reduce year by 1 
		auto y = year;
		if (month < 3)
			--y;

		return ((y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7);
	}

	constexpr std::size_t year_day() const {
		auto sum = day;
		for (std::size_t i = 1; i < month; ++i)
			sum += daytabs[static_cast<std::size_t>(isleap(year))][i];
    
		return sum;
	}

    Date &operator++()
    {
        if(day < 28) ++day;
        else if(day == 31){
            day = 1;
            month = month == 12 ? 1 : month + 1;
            if(month == 1)
                ++year;
        }
        else if(day == 30 && (month == 4 || month == 6 || month == 9 || month == 11)){
            day = 1;
            ++month;
        }
        else if(day == 29){
            if (month == 2) day = 1, month = 3;
            else ++day;
        }
        else{
            day = month == 2 ? (isleap(year) ? 29 : 1) : day + 1;
            if (day == 1) ++month;
        }

        return *this;
    }
    Date operator++(int){
        auto temp{ *this };
	    ++*this;
	    return temp;
    }

    Date &operator--(){
        std::size_t d = day, m = month, y = year;

        if (d != 1) --d;
        else if (m != 1){
            --m;
            d = daytabs[static_cast<std::size_t>(isleap(y))][m];
        }
        else{
            if (y == yearbase) throw std::runtime_error{"bad_date!"};
            m = 12;
            d = 31;
            --y;
        }
        day = d;
        month = m;
        year = y;

        return *this;
    }
    Date operator--(int){
        auto temp{*this};
        --*this;
        return temp;
    }

    friend bool operator<(const Date &d1, const Date &d2){
        return d1.year != d2.year ? d1.year < d2.year : d1.month != d2.month ? d1.month < d2.month
                                                               : d1.day < d2.day;
    }
    friend bool operator==(const Date &d1, const Date &d2){
        return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
    }
    friend std::size_t operator-(const Date &d1, const Date &d2){
        return d1.totaldays() - d2.totaldays();
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& date){
        static constexpr const char *pmons[] = 
                         {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

        static constexpr const char *pdays[] = {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
        };

        std::ostringstream ossr;

        ossr << std::setfill('0') << std::setw(2) << date.day;
        ossr << std::setfill(' ') << std::left;
        ossr << " " << pmons[date.month] << " " << date.year << " " << pdays[date.get_week()];
        return os << ossr.str();
    }
    friend std::istream& operator>>(std::istream& is, Date& date){
        std::size_t d, m, y;
        is >> d >> m >> y;
        date = Date{d, m, y};
        return is;
    }
    static Date random(){
        std::size_t y = Irand{1950, 2020}();

        std::size_t m = Irand{1, 12}();
        std::size_t d = Irand{1, daytabs[static_cast<std::size_t>(isleap(y))][m]}();

        return Date{d, m, y};
    }

private:
    std::size_t day{ 1 }, month{ 1 }, year{ 1900 };

    void set(std::size_t d_, std::size_t m_,std::size_t y_){
        if (!isvalid(d_, m_, y_))
			throw std::runtime_error{"bad_date!"};
        
		day = d_, month = m_, year = y_;
    }

    static constexpr std::size_t yearbase = 1900;
	static constexpr bool isleap(std::size_t y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); }
	static constexpr bool isvalid(std::size_t d, std::size_t m, std::size_t y){
		return y >= yearbase && m > 0 && m <= 12 && d > 0 && d <= daytabs[static_cast<std::size_t>(isleap(y))][m];
	}
    inline static constexpr std::size_t daytabs[][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	};
    
    constexpr std::size_t totaldays()const{
		return (year - 1900) * 365 + (year - 1901) / 4 + year_day();
	}
};

inline bool operator>(const Date& d1, const Date& d2) { return d2 < d1; }

inline bool operator>=(const Date& d1, const Date& d2) { return !(d1 < d2); }

inline bool operator<=(const Date& d1, const Date& d2) { return !(d2 < d1); }

inline bool operator!=(const Date& d1, const Date& d2) { return !(d1 == d2); }