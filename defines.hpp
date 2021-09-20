#define NOT_FOUND_MSG "Not Found"
#define BAD_REQUEST_MSG "Bad Request"
#define PERMISSION_MSG "Permission Denied"
#define OK_MSG "OK"
#define EMPTY_MSG "Empty"
#define NOT_ENOUGH_ROOM_MSG "Not Enough Room"
#define NO_RATING_MSG "No Rating"
#define NOT_ENOUGH_CREDIT_MSG "Not Enough Credit"
#define INSUFFICIENT_RATINGS_MSG "Insufficient Ratings"

#define SIGNUP_KEYWORD "signup"
#define LOGIN_KEYWORD "login"
#define LOGOUT_KEYWORD "logout"
#define WALLET_KEYWORD "wallet"
#define FILTERS_KEYWORD "filters"
#define RESERVES_KEYWORD "reserves"
#define COMMENTS_KEYWORD "comments"
#define RATINGS_KEYWORD "ratings"
#define HOTELS_KEYWORD "hotels"
#define DEFAULT_PRICE_FILTER_KEYWORD "default_price_filter"
#define SORT_KEYWORD "sort"

#define STANDARD_KEYWORD "standard"
#define DELUXE_KEYWORD "deluxe"
#define LUXURY_KEYWORD "luxury"
#define PREMIUM_KEYWORD "premium"

#define EMAIL_KEYWORD "email"
#define USERNAME_KEYWORD "username"
#define PASSWORD_KEYWORD "password"
#define AMOUNT_KEYWORD "amount"
#define MIN_STAR_KEYWORD "min_star"
#define MAX_STAR_KEYWORD "max_star"
#define MIN_PRICE_KEYWORD "min_price"
#define MAX_PRICE_KEYWORD "max_price"
#define TYPE_KEYWORD "type"
#define QUANTITY_KEYWORD "quantity"
#define CHECK_IN_KEYWORD "check_in"
#define CHECK_OUT_KEYWORD "check_out"
#define CITY_KEYWORD "city"
#define HOTEL_KEYWORD "hotel"
#define COMMENT_KEYWORD "comment"
#define MANUAL_WEIGHTS_KEYWORD "manual_weights"
#define ESTIMATED_WEIGHTS_KEYWORD "estimated_weights"

#define LOCATION_KEYWORD "location"
#define CLEANLINESS_KEYWORD "cleanliness"
#define STAFF_KEYWORD "staff"
#define FACILITIES_KEYWORD "facilities"
#define VALUE_FOR_MONEY_KEYWORD "value_for_money"
#define OVERALL_RATING_KEYWORD "overall_rating"

#define PRINT__STAR_KEYWORD "star: "
#define PRINT__OVERVIEW_KEYWORD "overview: "
#define PRINT__AMENITIES_KEYWORD "amenities: "
#define PRINT__CITY_KEYWORD "city: "
#define PRINT__LATITUDE_KEYWORD "latitude: "
#define PRINT__LONGITUDE_KEYWORD "longitude: "
#define PRINT__ROOMS_KEYWORD "#rooms:"
#define PRINT__PRICE_KEYWORD "price:"
#define PRINT__ID_KEYWORD "id: "
#define PRINT__HOTEL_KEYWORD "hotel: "
#define PRINT__ROOM_KEYWORD "room: " 
#define PRINT__QUANTITY_KEYWORD "quantity: "
#define PRINT__COST_KEYWORD "cost: "
#define PRINT__CHECK_IN_KEYWORD "check_in "
#define PRINT__CHECK_OUT_KEYWORD "check_out "

#define PRINT__LOCATION_KEYWORD "location: "
#define PRINT__CLEANLINESS_KEYWORD "cleanliness: "
#define PRINT__STAFF_KEYWORD "staff: "
#define PRINT__FACILITIES_KEYWORD "facilities: "
#define PRINT__VALUE_FOR_MONEY_KEYWORD "value_for_money: "
#define PRINT__OVERALL_RATING_KEYWORD "overall_rating: "

#define TRUE_KEYWORD "true"
#define FALSE_KEYWORD "false"

#define DEFAULT_PRICE_FILTER_PRINT_MSG "* Results have been filtered by the default price filter."

#define PROPERTY_KEYWORD "property"
#define ORDER_KEYWORD "order"
#define ASCENDING_KEYWORD "ascending"
#define DESCENDING_KEYWORD "descending"
#define NUM_SORT_FEATURES 11

#define ID_KEYWORD "id"
#define NAME_KEYWORD "name" 
#define STAR_RATING_KEYWORD "star_rating"
#define STANDARD_ROOM_PRICE_KEYWORD "standard_room_price"
#define DELUXE_ROOM_PRICE_KEYWORD "deluxe_room_price"
#define LUXURY_ROOM_PRICE_KEYWORD "luxury_room_price"
#define PREMIUM_ROOM_PRICE_KEYWORD "premium_room_price"
#define AVERAGE_ROOM_PRICE_KEYWORD "average_room_price"
#define RATING_OVERALL_KEYWORD "rating_overall"
#define RATING_PERSONAL_KEYWORD "rating_personal"

#define STANDARD_ROOM_INDEX 0
#define DELUXE_ROOM_INDEX 1
#define LUXURY_ROOM_INDEX 2
#define PREMIUM_ROOM_INDEX 3

#define ACTIVE_KEYWORD "active"
#define NUM_WEIGHTS 5
#define LOCATION_INDEX 0
#define CLEANLINESS_INDEX 1
#define STAFF_INDEX 2
#define FACILITIES_INDEX 3
#define VALUE_FOR_MONEY_INDEX 4

#define FIX_PRECISION std::fixed << setprecision(2) << 

#define SUFFICIENT_RATINGS 5
#define RANDOM_SEED time(0)
#define MAX_WEIGHT 5
#define MIN_WEIGHT 1
#define MAX_ITERATIONS 200000
#define EPSILON 1e-7
#define ALPHA 0.2