-------------------------------------------------------------------------------
--! @file toplevel.vhd
--
--! @brief Toplevel of Nios CN FPGA appif dual processor design
--
--! @details This is the toplevel of the Nios CN FPGA appif dual processor
--! design for the INK DE2-115 Evaluation Board.
--
-------------------------------------------------------------------------------
--
--    (c) B&R, 2013
--
--    Redistribution and use in source and binary forms, with or without
--    modification, are permitted provided that the following conditions
--    are met:
--
--    1. Redistributions of source code must retain the above copyright
--       notice, this list of conditions and the following disclaimer.
--
--    2. Redistributions in binary form must reproduce the above copyright
--       notice, this list of conditions and the following disclaimer in the
--       documentation and/or other materials provided with the distribution.
--
--    3. Neither the name of B&R nor the names of its
--       contributors may be used to endorse or promote products derived
--       from this software without prior written permission. For written
--       permission, please contact office@br-automation.com
--
--    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
--    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
--    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
--    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
--    COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
--    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
--    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
--    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
--    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
--    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
--    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--    POSSIBILITY OF SUCH DAMAGE.
--
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity toplevel is
    port (
        -- 50 MHZ CLK IN
        EXT_CLK             :  in std_logic;
        -- PHY0 Interface
        PHY0_GXCLK          :  out std_logic;
        PHY0_RXCLK          :  in std_logic;
        PHY0_RXER           :  in std_logic;
        PHY0_RXDV           :  in std_logic;
        PHY0_RXD            :  in std_logic_vector(3 downto 0);
        PHY0_TXCLK          :  in std_logic;
        PHY0_TXER           :  out std_logic;
        PHY0_TXEN           :  out std_logic;
        PHY0_TXD            :  out std_logic_vector(3 downto 0);
        PHY0_LINK           :  in std_logic;
        PHY0_MDIO           :  inout std_logic;
        PHY0_MDC            :  out std_logic;
        PHY0_RESET_n        :  out std_logic;
        -- PHY1 Interface
        PHY1_GXCLK          :  out std_logic;
        PHY1_RXCLK          :  in std_logic;
        PHY1_RXER           :  in std_logic;
        PHY1_RXDV           :  in std_logic;
        PHY1_RXD            :  in std_logic_vector(3 downto 0);
        PHY1_TXCLK          :  in std_logic;
        PHY1_TXER           :  out std_logic;
        PHY1_TXEN           :  out std_logic;
        PHY1_TXD            :  out std_logic_vector(3 downto 0);
        PHY1_LINK           :  in std_logic;
        PHY1_MDIO           :  inout std_logic;
        PHY1_MDC            :  out std_logic;
        PHY1_RESET_n        :  out std_logic;
        -- EPCS
        EPCS_DCLK           :  out std_logic;
        EPCS_SCE            :  out std_logic;
        EPCS_SDO            :  out std_logic;
        EPCS_DATA0          :  in std_logic;
        -- 2 MB SRAM
        SRAM_CE_n           :  out std_logic;
        SRAM_OE_n           :  out std_logic;
        SRAM_WE_n           :  out std_logic;
        SRAM_ADDR           :  out std_logic_vector(20 downto 1);
        SRAM_BE_n           :  out std_logic_vector(1 downto 0);
        SRAM_DQ             :  inout std_logic_vector(15 downto 0);
        -- 64 MBx2 SDRAM
        SDRAM_CLK           : out  std_logic;
        SDRAM_CAS_n         : out  std_logic;
        SDRAM_CKE           : out  std_logic;
        SDRAM_CS_n          : out  std_logic;
        SDRAM_RAS_n         : out  std_logic;
        SDRAM_WE_n          : out  std_logic;
        SDRAM_ADDR          : out  std_logic_vector(12 downto 0);
        SDRAM_BA            : out  std_logic_vector(1 downto 0);
        SDRAM_DQM           : out  std_logic_vector(3 downto 0);
        SDRAM_DQ            : inout  std_logic_vector(31 downto 0);
        -- SPI
        SPI_CLK             : in std_logic;
        SPI_MOSI            : in std_logic;
        SPI_SEL_n           : in std_logic;
        SPI_MISO            : out std_logic;
        -- SYNC IRQ
        SYNC_IRQ            : out std_logic;
        -- SPI Master
        SPIM_CLK            : out std_logic;
        SPIM_MOSI           : out std_logic;
        SPIM_SEL_n          : out std_logic;
        SPIM_MISO           : in std_logic;
        -- SYNC IRQ IN
        SYNC_IRQ_IN         : in std_logic;
        -- NODE_SWITCH
        NODE_SWITCH         : in std_logic_vector(7 downto 0);
        -- KEY
        KEY                 : in std_logic_vector(3 downto 0);
        -- LED
        LEDG                : out std_logic_vector(7 downto 0);
        LEDR                : out std_logic_vector(15 downto 0);
        -- HEX LED
        HEX0                : out std_logic_vector(6 downto 0);
        HEX1                : out std_logic_vector(6 downto 0);
        HEX2                : out std_logic_vector(6 downto 0);
        HEX3                : out std_logic_vector(6 downto 0);
        HEX4                : out std_logic_vector(6 downto 0);
        HEX5                : out std_logic_vector(6 downto 0);
        HEX6                : out std_logic_vector(6 downto 0);
        HEX7                : out std_logic_vector(6 downto 0);
        -- BENCHMARK_OUT
        BENCHMARK_PCP       : out std_logic_vector(7 downto 0);
        BENCHMARK_APP       : out std_logic_vector(7 downto 0);
        -- LCD
        LCD_ON              : out std_logic;
        LCD_BLON            : out std_logic;
        LCD_DQ              : inout std_logic_vector(7 downto 0);
        LCD_E               : out std_logic;
        LCD_RS              : out std_logic;
        LCD_RW              : out std_logic
    );
end toplevel;

architecture rtl of toplevel is

    component cn_SPI_ap_pcp is
        port (
            clk50_clk                               : in    std_logic                     := 'X';
            clk100_clk                              : in    std_logic                     := 'X';
            clk25_clk                               : in    std_logic                     := 'X';
            reset_reset_n                           : in    std_logic                     := 'X';
            -- PHY 0
            powerlink_0_mii0_phyMii0_TxClk          : in    std_logic                     := 'X';
            powerlink_0_mii0_phyMii0_TxEn           : out   std_logic;
            powerlink_0_mii0_phyMii0_TxEr           : out   std_logic;
            powerlink_0_mii0_phyMii0_TxDat          : out   std_logic_vector(3 downto 0);
            powerlink_0_mii0_phyMii0_RxClk          : in    std_logic                     := 'X';
            powerlink_0_mii0_phyMii0_RxDv           : in    std_logic                     := 'X';
            powerlink_0_mii0_phyMii0_RxEr           : in    std_logic                     := 'X';
            powerlink_0_mii0_phyMii0_RxDat          : in    std_logic_vector(3 downto 0)  := (others => 'X');
            powerlink_0_mii0_phyMii1_RxEr           : in    std_logic                     := 'X';
            powerlink_0_phym0_SMIClk                : out   std_logic;
            powerlink_0_phym0_SMIDat                : inout std_logic                     := 'X';
            powerlink_0_phym0_Rst_n                 : out   std_logic;
            powerlink_0_phyl_phy0_link              : in    std_logic                     := 'X';
            -- PHY 1
            powerlink_0_mii1_TxClk                  : in    std_logic                     := 'X';
            powerlink_0_mii1_TxEn                   : out   std_logic;
            powerlink_0_mii1_TxEr                   : out   std_logic;
            powerlink_0_mii1_TxDat                  : out   std_logic_vector(3 downto 0);
            powerlink_0_mii1_RxClk                  : in    std_logic                     := 'X';
            powerlink_0_mii1_RxDv                   : in    std_logic                     := 'X';
            powerlink_0_mii1_RxDat                  : in    std_logic_vector(3 downto 0)  := (others => 'X');
            powerlink_0_phym1_SMIClk                : out   std_logic;
            powerlink_0_phym1_SMIDat                : inout std_logic                     := 'X';
            powerlink_0_phym1_Rst_n                 : out   std_logic;
            powerlink_0_phyl_phy1_link              : in    std_logic                     := 'X';
            -- SRAM
            tri_state_0_tcm_address_out             : out   std_logic_vector(20 downto 0);
            tri_state_0_tcm_byteenable_n_out        : out   std_logic_vector(1 downto 0);
            tri_state_0_tcm_read_n_out              : out   std_logic;
            tri_state_0_tcm_write_n_out             : out   std_logic;
            tri_state_0_tcm_data_out                : inout std_logic_vector(15 downto 0) := (others => 'X');
            tri_state_0_tcm_chipselect_n_out        : out   std_logic;
            -- NODE SWITCHES
            node_switch_pio_export                  : in    std_logic_vector(7 downto 0)  := (others => 'X');
            -- POWERLINK LEDs
            status_led_pio_export                   : out   std_logic_vector(1 downto 0);
            -- FLASH
            epcs_flash_dclk                         : out   std_logic;
            epcs_flash_sce                          : out   std_logic;
            epcs_flash_sdo                          : out   std_logic;
            epcs_flash_data0                        : in    std_logic                     := 'X';
            -- USER LCD
            lcd_RS                                  : out   std_logic;
            lcd_RW                                  : out   std_logic;
            lcd_data                                : inout std_logic_vector(7 downto 0)  := (others => 'X');
            lcd_E                                   : out   std_logic;
            -- USE GPIOs
            hex_pio_export                          : out   std_logic_vector(31 downto 0);
            ledr_pio_export                         : out   std_logic_vector(15 downto 0);
            key_pio_export                          : in    std_logic_vector(3 downto 0)  := (others => 'X');
            -- PCP SPI BRIDGE
            plkif_0_spi_bridge_0_clk                : in    std_logic                     := 'X';
            plkif_0_spi_bridge_0_sel_n              : in    std_logic                     := 'X';
            plkif_0_spi_bridge_0_mosi               : in    std_logic                     := 'X';
            plkif_0_spi_bridge_0_miso               : out   std_logic;
            -- AP SPI MASTER
            spi_master_external_MISO                : in    std_logic                     := 'X';
            spi_master_external_MOSI                : out   std_logic;
            spi_master_external_SCLK                : out   std_logic;
            spi_master_external_SS_n                : out   std_logic;
            -- BENCHMARK AP
            app_0_benchmark_pio_export              : out   std_logic_vector(7 downto 0);
            -- BENCHMARK PCP
            pcp_0_benchmark_pio_export              : out   std_logic_vector(7 downto 0);
            -- SYNC IRQ
            powerlink_0_ap_ex_irq_export            : out   std_logic;
            app_0_sync_irq_in_export                : in   std_logic;
            -- SDRAM
            app_0_sdram_0_addr                      : out   std_logic_vector(12 downto 0);
            app_0_sdram_0_ba                        : out   std_logic_vector(1 downto 0);
            app_0_sdram_0_cas_n                     : out   std_logic;
            app_0_sdram_0_cke                       : out   std_logic;
            app_0_sdram_0_cs_n                      : out   std_logic;
            app_0_sdram_0_dq                        : inout std_logic_vector(31 downto 0) := (others => 'X');
            app_0_sdram_0_dqm                       : out   std_logic_vector(3 downto 0);
            app_0_sdram_0_ras_n                     : out   std_logic;
            app_0_sdram_0_we_n                      : out   std_logic
        );
    end component cn_SPI_ap_pcp;

    -- PLL component
    component pll
        port (
            inclk0  : in std_logic;
            c0      : out std_logic;
            c1      : out std_logic;
            c2      : out std_logic;
            c3      : out std_logic;
            locked  : out std_logic
        );
    end component;

    signal clk25            : std_logic;
    signal clk50            : std_logic;
    signal clk100           : std_logic;
    signal pllLocked        : std_logic;
    signal sramAddr         : std_logic_vector(SRAM_ADDR'high downto 0);
    signal plk_status_error : std_logic_vector(1 downto 0);

    type tSevenSegArray is array (natural range <>) of std_logic_vector(6 downto 0);
    constant cNumberOfHex   : natural := 8;
    signal hex              : std_logic_vector(cNumberOfHex*4-1 downto 0);
    signal sevenSegArray    : tSevenSegArray(cNumberOfHex-1 downto 0);

begin
    SRAM_ADDR   <= sramAddr(SRAM_ADDR'range);

    PHY0_GXCLK  <= '0';
    PHY1_GXCLK  <= '0';

    LCD_ON      <= '1';
    LCD_BLON    <= '1';

    LEDG        <= "000000" & plk_status_error;

    inst: cn_SPI_ap_pcp
        port map (
            clk25_clk                                       => clk25,
            clk50_clk                                       => clk50,
            clk100_clk                                      => clk100,
            reset_reset_n                                   => pllLocked,
            -- PHY 0
            powerlink_0_mii0_phyMii0_TxClk                  => PHY0_TXCLK,
            powerlink_0_mii0_phyMii0_TxEn                   => PHY0_TXEN,
            powerlink_0_mii0_phyMii0_TxEr                   => PHY0_TXER,
            powerlink_0_mii0_phyMii0_TxDat                  => PHY0_TXD,
            powerlink_0_mii0_phyMii0_RxClk                  => PHY0_RXCLK,
            powerlink_0_mii0_phyMii0_RxDv                   => PHY0_RXDV,
            powerlink_0_mii0_phyMii0_RxEr                   => PHY0_RXER,
            powerlink_0_mii0_phyMii0_RxDat                  => PHY0_RXD,
            powerlink_0_phym0_SMIClk                        => PHY0_MDC,
            powerlink_0_phym0_SMIDat                        => PHY0_MDIO,
            powerlink_0_phym0_Rst_n                         => PHY0_RESET_n,
            powerlink_0_phyl_phy0_link                      => open,
            -- PHY 1
            powerlink_0_mii1_TxClk                          => PHY1_TXCLK,
            powerlink_0_mii1_TxEn                           => PHY1_TXEN,
            powerlink_0_mii1_TxEr                           => PHY1_TXER,
            powerlink_0_mii1_TxDat                          => PHY1_TXD,
            powerlink_0_mii1_RxClk                          => PHY1_RXCLK,
            powerlink_0_mii1_RxDv                           => PHY1_RXDV,
            powerlink_0_mii1_RxDat                          => PHY1_RXD,
            powerlink_0_mii0_phyMii1_RxEr                   => PHY1_RXER,
            powerlink_0_phym1_SMIClk                        => PHY1_MDC,
            powerlink_0_phym1_SMIDat                        => PHY1_MDIO,
            powerlink_0_phym1_Rst_n                         => PHY1_RESET_n,
            powerlink_0_phyl_phy1_link                      => open,
            -- SRAM
            tri_state_0_tcm_address_out                     => sramAddr,
            tri_state_0_tcm_read_n_out                      => SRAM_OE_n,
            tri_state_0_tcm_byteenable_n_out                => SRAM_BE_n,
            tri_state_0_tcm_write_n_out                     => SRAM_WE_n,
            tri_state_0_tcm_data_out                        => SRAM_DQ,
            tri_state_0_tcm_chipselect_n_out                => SRAM_CE_n,
            -- NODE SWITCHES
            node_switch_pio_export                          => NODE_SWITCH,
            -- POWERLINK LEDs
            status_led_pio_export                           => plk_status_error,
            -- FLASH
            epcs_flash_dclk                                 => EPCS_DCLK,
            epcs_flash_sce                                  => EPCS_SCE,
            epcs_flash_sdo                                  => EPCS_SDO,
            epcs_flash_data0                                => EPCS_DATA0,
            -- USER LCD
            lcd_data                                        => LCD_DQ,
            lcd_E                                           => LCD_E,
            lcd_RS                                          => LCD_RS,
            lcd_RW                                          => LCD_RW,
            -- USER GPIOs
            hex_pio_export                                  => hex,
            ledr_pio_export                                 => LEDR,
            key_pio_export                                  => KEY,
            -- PCP SPI BRIDGE
            plkif_0_spi_bridge_0_clk                        => SPI_CLK,
            plkif_0_spi_bridge_0_sel_n                      => SPI_SEL_n,
            plkif_0_spi_bridge_0_mosi                       => SPI_MOSI,
            plkif_0_spi_bridge_0_miso                       => SPI_MISO,
            -- AP SPI MASTER
            spi_master_external_MISO                        => SPIM_MISO,
            spi_master_external_MOSI                        => SPIM_MOSI,
            spi_master_external_SCLK                        => SPIM_CLK,
            spi_master_external_SS_n                        => SPIM_SEL_n,
            -- BENCHMARK AP
            app_0_benchmark_pio_export                      => BENCHMARK_APP,
            -- BENCHMARK PCP
            pcp_0_benchmark_pio_export                      => BENCHMARK_PCP,
            -- SYNC IRQ
            powerlink_0_ap_ex_irq_export                    => SYNC_IRQ,
            app_0_sync_irq_in_export                        => SYNC_IRQ_IN,
            -- SDRAM
            app_0_sdram_0_addr                              => SDRAM_ADDR,
            app_0_sdram_0_ba                                => SDRAM_BA,
            app_0_sdram_0_cas_n                             => SDRAM_CAS_n,
            app_0_sdram_0_cke                               => SDRAM_CKE,
            app_0_sdram_0_cs_n                              => SDRAM_CS_n,
            app_0_sdram_0_dq                                => SDRAM_DQ,
            app_0_sdram_0_dqm                               => SDRAM_DQM,
            app_0_sdram_0_ras_n                             => SDRAM_RAS_n,
            app_0_sdram_0_we_n                              => SDRAM_WE_n
        );

    -- Pll Instance
    pllInst : pll
        port map (
            inclk0  => EXT_CLK,
            c0      => clk50,
            c1      => clk100,
            c2      => clk25,
            c3      => SDRAM_CLK,
            locked  => pllLocked
        );

    -- bcd to 7 segment
    genBcdTo7Seg : for i in cNumberOfHex-1 downto 0 generate
        signal tmpHex : std_logic_vector(3 downto 0);
        signal tmpSev : std_logic_vector(6 downto 0);
    begin
        tmpHex <= hex((i+1)*4-1 downto i*4);
        sevenSegArray(i) <= tmpSev;

        bcdTo7Seg0 : entity work.bcd2led
            port map (
                iBcdVal => tmpHex,
                oLed    => open,
                onLed   => tmpSev
            );
    end generate genBcdTo7Seg;

    -- assign outports to array
    HEX0 <= sevenSegArray(0);
    HEX1 <= sevenSegArray(1);
    HEX2 <= sevenSegArray(2);
    HEX3 <= sevenSegArray(3);
    HEX4 <= sevenSegArray(4);
    HEX5 <= sevenSegArray(5);
    HEX6 <= sevenSegArray(6);
    HEX7 <= sevenSegArray(7);
end rtl;
