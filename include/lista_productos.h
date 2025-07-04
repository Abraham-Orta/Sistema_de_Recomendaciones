#ifndef LISTA_PRODUCTOS_H
#define LISTA_PRODUCTOS_H

#include <vector>
#include "producto.h"

inline std::vector<Producto> obtenerListaProductos() {
    return {
        // Electrónica (20)
        {"Smartphone Galaxy S24", "Teléfono inteligente de última generación", "Samsung", "Electrónica", "E001", 18000.0},
        {"iPhone 15 Pro", "Teléfono inteligente Apple", "Apple", "Electrónica", "E002", 25000.0},
        {"Laptop Inspiron 15", "Computadora portátil de alto rendimiento", "Dell", "Electrónica", "E003", 17000.0},
        {"MacBook Air M2", "Portátil ultraligero", "Apple", "Electrónica", "E004", 28000.0},
        {"Smart TV 55'' 4K", "Televisor inteligente 4K UHD", "LG", "Electrónica", "E005", 12000.0},
        {"Smart TV 65'' OLED", "Televisor OLED de alta definición", "Sony", "Electrónica", "E006", 35000.0},
        {"Auriculares inalámbricos WH-1000XM5", "Auriculares con cancelación de ruido", "Sony", "Electrónica", "E007", 6000.0},
        {"AirPods Pro 2", "Auriculares inalámbricos Apple", "Apple", "Electrónica", "E008", 5500.0},
        {"Tablet Galaxy Tab S8", "Tableta Android de alto rendimiento", "Samsung", "Electrónica", "E009", 9000.0},
        {"iPad Pro 11", "Tableta profesional Apple", "Apple", "Electrónica", "E010", 18000.0},
        {"Cámara Digital EOS 250D", "Cámara réflex digital", "Canon", "Electrónica", "E011", 14000.0},
        {"Cámara Mirrorless Alpha 7", "Cámara sin espejo profesional", "Sony", "Electrónica", "E012", 32000.0},
        {"Smartwatch Versa 4", "Reloj inteligente deportivo", "Fitbit", "Electrónica", "E013", 3500.0},
        {"Smartwatch Series 9", "Reloj inteligente Apple", "Apple", "Electrónica", "E014", 9000.0},
        {"Bocina Bluetooth SoundLink", "Bocina portátil inalámbrica", "Bose", "Electrónica", "E015", 2500.0},
        {"Bocina Bluetooth Flip 6", "Bocina portátil resistente al agua", "JBL", "Electrónica", "E016", 2200.0},
        {"Monitor 27'' 2K", "Monitor de alta resolución", "Acer", "Electrónica", "E017", 4800.0},
        {"Monitor 32'' 4K", "Monitor profesional para diseño", "Dell", "Electrónica", "E018", 9500.0},
        {"Router WiFi 6", "Router de alta velocidad", "TP-Link", "Electrónica", "E019", 1800.0},
        {"Disco SSD 1TB", "Almacenamiento sólido rápido", "Samsung", "Electrónica", "E020", 2100.0},

        // Hogar y cocina (20)
        {"Cafetera Espresso", "Cafetera automática para espresso", "DeLonghi", "Hogar y cocina", "H001", 3500.0},
        {"Cafetera de goteo", "Cafetera programable", "Hamilton Beach", "Hogar y cocina", "H002", 1200.0},
        {"Aspiradora sin bolsa", "Aspiradora ciclónica potente", "Philips", "Hogar y cocina", "H003", 2500.0},
        {"Aspiradora robot", "Robot aspirador inteligente", "iRobot", "Hogar y cocina", "H004", 7000.0},
        {"Juego de sábanas Queen", "Sábanas de algodón 400 hilos", "Casa Blanca", "Hogar y cocina", "H005", 900.0},
        {"Juego de sábanas King", "Sábanas suaves y frescas", "Luna", "Hogar y cocina", "H006", 1100.0},
        {"Olla de presión", "Olla de presión de acero inoxidable", "Presto", "Hogar y cocina", "H007", 1300.0},
        {"Sartén antiadherente", "Sartén de 28cm", "T-fal", "Hogar y cocina", "H008", 600.0},
        {"Licuadora profesional", "Licuadora de alta potencia", "Oster", "Hogar y cocina", "H009", 1800.0},
        {"Licuadora personal", "Licuadora compacta para smoothies", "NutriBullet", "Hogar y cocina", "H010", 950.0},
        {"Mesa auxiliar", "Mesa pequeña para sala", "Ikea", "Hogar y cocina", "H011", 850.0},
        {"Silla plegable", "Silla ligera y resistente", "Home Collection", "Hogar y cocina", "H012", 400.0},
        {"Microondas 20L", "Microondas compacto", "Mabe", "Hogar y cocina", "H013", 1700.0},
        {"Refrigerador 14 pies", "Refrigerador con congelador", "Whirlpool", "Hogar y cocina", "H014", 12000.0},
        {"Tostadora 2 rebanadas", "Tostadora eléctrica", "Black+Decker", "Hogar y cocina", "H015", 500.0},
        {"Batidora de mano", "Batidora eléctrica", "KitchenAid", "Hogar y cocina", "H016", 1300.0},
        {"Freidora de aire", "Freidora sin aceite", "Ninja", "Hogar y cocina", "H017", 2500.0},
        {"Plancha de vapor", "Plancha para ropa", "Rowenta", "Hogar y cocina", "H018", 900.0},
        {"Ventilador de torre", "Ventilador silencioso", "Honeywell", "Hogar y cocina", "H019", 1600.0},
        {"Calefactor portátil", "Calefactor eléctrico", "Imaco", "Hogar y cocina", "H020", 1200.0},

        // Moda y Accesorios (20)
        {"Camiseta básica", "Camiseta de algodón unisex", "H&M", "Moda y Accesorios", "M001", 250.0},
        {"Vaqueros slim fit", "Pantalón de mezclilla azul", "Levi's", "Moda y Accesorios", "M002", 1200.0},
        {"Zapatillas deportivas", "Tenis para correr", "Nike", "Moda y Accesorios", "M003", 1800.0},
        {"Reloj de pulsera", "Reloj analógico clásico", "Casio", "Moda y Accesorios", "M004", 900.0},
        {"Bolso tote", "Bolso grande de tela", "Zara", "Moda y Accesorios", "M005", 700.0},
        {"Gafas de sol polarizadas", "Lentes de sol UV400", "Ray-Ban", "Moda y Accesorios", "M006", 1500.0},
        {"Sudadera con capucha", "Sudadera cómoda", "Adidas", "Moda y Accesorios", "M007", 950.0},
        {"Pantalón deportivo", "Pantalón para ejercicio", "Puma", "Moda y Accesorios", "M008", 800.0},
        {"Chaqueta impermeable", "Chaqueta ligera para lluvia", "Columbia", "Moda y Accesorios", "M009", 1600.0},
        {"Vestido casual", "Vestido de verano", "Bershka", "Moda y Accesorios", "M010", 1100.0},
        {"Sandalias planas", "Sandalias cómodas", "C&A", "Moda y Accesorios", "M011", 400.0},
        {"Botines de piel", "Botines para dama", "Flexi", "Moda y Accesorios", "M012", 1700.0},
        {"Cinturón de cuero", "Cinturón clásico", "Dockers", "Moda y Accesorios", "M013", 350.0},
        {"Corbata de seda", "Corbata elegante", "Massimo Dutti", "Moda y Accesorios", "M014", 600.0},
        {"Blusa manga larga", "Blusa formal", "Mango", "Moda y Accesorios", "M015", 800.0},
        {"Falda plisada", "Falda elegante", "Pull&Bear", "Moda y Accesorios", "M016", 900.0},
        {"Calcetines deportivos", "Pack de 3 pares", "Reebok", "Moda y Accesorios", "M017", 200.0},
        {"Reloj digital", "Reloj resistente al agua", "Timex", "Moda y Accesorios", "M018", 1200.0},
        {"Mochila urbana", "Mochila para laptop", "Totto", "Moda y Accesorios", "M019", 950.0},
        {"Bufanda de lana", "Bufanda para invierno", "Springfield", "Moda y Accesorios", "M020", 400.0},

        // Deportes y Aire Libre (20)
        {"Balón de fútbol", "Balón profesional talla 5", "Adidas", "Deportes y Aire Libre", "D001", 600.0},
        {"Balón de baloncesto", "Balón oficial", "Spalding", "Deportes y Aire Libre", "D002", 700.0},
        {"Mancuernas 5kg", "Par de mancuernas", "Everlast", "Deportes y Aire Libre", "D003", 800.0},
        {"Bicicleta de montaña", "Bicicleta con suspensión", "Benotto", "Deportes y Aire Libre", "D004", 6500.0},
        {"Tienda de campaña 4p", "Tienda para 4 personas", "Ozark Trail", "Deportes y Aire Libre", "D005", 3200.0},
        {"Ropa deportiva", "Conjunto deportivo", "Under Armour", "Deportes y Aire Libre", "D006", 1200.0},
        {"Botella de agua reutilizable", "Botella de acero inoxidable", "CamelBak", "Deportes y Aire Libre", "D007", 350.0},
        {"Cuerda para saltar", "Cuerda ajustable", "Nike", "Deportes y Aire Libre", "D008", 180.0},
        {"Colchoneta de yoga", "Tapete antideslizante", "Gaiam", "Deportes y Aire Libre", "D009", 400.0},
        {"Raqueta de tenis", "Raqueta ligera", "Wilson", "Deportes y Aire Libre", "D010", 1500.0},
        {"Guantes de gimnasio", "Guantes antideslizantes", "Adidas", "Deportes y Aire Libre", "D011", 300.0},
        {"Casco para ciclismo", "Casco ajustable", "Specialized", "Deportes y Aire Libre", "D012", 900.0},
        {"Patines en línea", "Patines para adultos", "Rollerblade", "Deportes y Aire Libre", "D013", 2200.0},
        {"Saco de dormir", "Saco térmico", "Coleman", "Deportes y Aire Libre", "D014", 950.0},
        {"Lámpara de camping", "Lámpara LED recargable", "Energizer", "Deportes y Aire Libre", "D015", 400.0},
        {"Bastones de trekking", "Par de bastones", "Black Diamond", "Deportes y Aire Libre", "D016", 1100.0},
        {"Chaleco salvavidas", "Chaleco para deportes acuáticos", "Speedo", "Deportes y Aire Libre", "D017", 850.0},
        {"Gorra deportiva", "Gorra transpirable", "Nike", "Deportes y Aire Libre", "D018", 250.0},
        {"Bicicleta urbana", "Bicicleta ligera para ciudad", "Mercurio", "Deportes y Aire Libre", "D019", 5200.0},
        {"Bolsa de deporte", "Bolsa grande para gimnasio", "Puma", "Deportes y Aire Libre", "D020", 700.0},

        // Cuidado personal y belleza (20)
        {"Crema hidratante facial", "Crema para piel seca", "Nivea", "Cuidado personal y belleza", "B001", 180.0},
        {"Perfume floral", "Fragancia para dama", "Carolina Herrera", "Cuidado personal y belleza", "B002", 2100.0},
        {"Champú anticaspa", "Champú para uso diario", "Head & Shoulders", "Cuidado personal y belleza", "B003", 120.0},
        {"Maquillaje compacto", "Polvo compacto mate", "Maybelline", "Cuidado personal y belleza", "B004", 250.0},
        {"Cepillo de dientes eléctrico", "Cepillo recargable", "Oral-B", "Cuidado personal y belleza", "B005", 600.0},
        {"Secador de pelo", "Secador profesional", "Remington", "Cuidado personal y belleza", "B006", 950.0},
        {"Plancha para cabello", "Plancha de cerámica", "Babyliss", "Cuidado personal y belleza", "B007", 1100.0},
        {"Crema antiarrugas", "Crema rejuvenecedora", "L'Oréal", "Cuidado personal y belleza", "B008", 350.0},
        {"Desodorante roll-on", "Desodorante sin alcohol", "Rexona", "Cuidado personal y belleza", "B009", 70.0},
        {"Gel de baño", "Gel hidratante para ducha", "Palmolive", "Cuidado personal y belleza", "B010", 90.0},
        {"Afeitadora eléctrica", "Afeitadora recargable", "Philips", "Cuidado personal y belleza", "B011", 1300.0},
        {"Esmalte de uñas", "Esmalte de larga duración", "Sally Hansen", "Cuidado personal y belleza", "B012", 120.0},
        {"Loción corporal", "Loción hidratante", "Vaseline", "Cuidado personal y belleza", "B013", 150.0},
        {"Mascarilla facial", "Mascarilla purificante", "Garnier", "Cuidado personal y belleza", "B014", 80.0},
        {"Crema para manos", "Crema nutritiva", "Neutrogena", "Cuidado personal y belleza", "B015", 90.0},
        {"Protector solar SPF50", "Protección solar alta", "Banana Boat", "Cuidado personal y belleza", "B016", 220.0},
        {"Tijeras para uñas", "Tijeras de acero inoxidable", "Revlon", "Cuidado personal y belleza", "B017", 60.0},
        {"Cepillo para cabello", "Cepillo desenredante", "Conair", "Cuidado personal y belleza", "B018", 130.0},
        {"Crema depilatoria", "Crema para piel sensible", "Veet", "Cuidado personal y belleza", "B019", 100.0},
        {"Kit de maquillaje", "Set completo de maquillaje", "MAC", "Cuidado personal y belleza", "B020", 1800.0}
    };
}

#endif // LISTA_PRODUCTOS_H