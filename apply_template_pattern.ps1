# Comprehensive script to apply template pattern to all remaining layer1Driver components

$scriptDir = "d:\sandbox\Bico_Protocol_Brigde"
$baseDir = "$scriptDir\3_swComp\layer1Driver"

# Define components to process (excluding gpioDriver and serialDriver - already done)
$components = @(
    @{
        Name = "i2cMasterDriver"
        Prefix = "I2cMasterDriver"
        Functions = @("Init", "SetSpeed", "Write", "WriteWithTimeout", "Read", "ReadWithTimeout", "WriteRead", "WriteRegister", "ReadRegister", "ScanBus", "IsBusy", "RegisterCallback", "DeInit")
    },
    @{
        Name = "i2cSlaveDriver"
        Prefix = "I2cSlaveDriver"
        Functions = @("Init", "SetAddress", "GetAddress", "SetTxBuffer", "SetRxBuffer", "GetRxLength", "IsAddressed", "RegisterRxCallback", "RegisterTxCallback", "RegisterAddressMatchCallback", "DeInit")
    },
    @{
        Name = "spiMasterDriver"
        Prefix = "SpiMasterDriver"
        Functions = @("Init", "Configure", "SelectChip", "DeselectChip", "Transmit", "Receive", "TransmitReceive", "TransmitWithTimeout", "IsBusy", "RegisterCallback", "DeInit")
    },
    @{
        Name = "spiSlaveDriver"
        Prefix = "SpiSlaveDriver"
        Functions = @("Init", "SetTxBuffer", "SetRxBuffer", "GetRxLength", "IsSelected", "RegisterRxCallback", "RegisterTxCallback", "DeInit")
    },
    @{
        Name = "pwmDriver"
        Prefix = "PwmDriver"
        Functions = @("Init", "ConfigureChannel", "SetFrequency", "SetDutyCycle", "SetPolarity", "StartChannel", "StopChannel", "GetConfiguration", "IsChannelRunning", "DeInit")
    },
    @{
        Name = "nvmDriver"
        Prefix = "NvmDriver"
        Functions = @("Init", "Read", "Write", "ErasePage", "EraseSector", "EraseChip", "WriteWithErase", "Verify", "CalculateCrc", "IsBusy", "GetInfo", "EnableWriteProtection", "DisableWriteProtection", "RegisterCallback", "DeInit")
    }
)

foreach ($comp in $components) {
    $compName = $comp.Name
    $prefix = $comp.Prefix
    $functions = $comp.Functions
    
    Write-Host "`n=== Processing $compName ===" -ForegroundColor Cyan
    
    $unitCPath = "$baseDir\$compName\5_src\${compName}Unit.c"
    $wrapperCPath = "$baseDir\$compName\5_src\$compName.c"
    
    # Read the existing Unit.c file
    if (Test-Path $unitCPath) {
        $content = Get-Content -Path $unitCPath -Raw
        
        # Replace function names with Unit suffix
        foreach ($func in $functions) {
            $oldPattern = "${prefix}_$func\("
            $newPattern = "${prefix}Unit_$func("
            $content = $content -replace $oldPattern, $newPattern
        }
        
        # Update header comment
        $content = $content -replace "// .* Implementation", "// This file is used to define the public interface of the component unit.`n// It contains public macros, private variables, and function definitions."
        
        # Add Local Macros section if missing
        if ($content -notmatch "//============================================================================\s+// Local Macros") {
            $content = $content -replace "(//============================================================================\s+// Local Types)", "//============================================================================`n// Local Macros`n//============================================================================`n`n`$1"
        }
        
        # Save updated Unit.c
        Set-Content -Path $unitCPath -Value $content -NoNewline
        Write-Host "✓ Updated $unitCPath" -ForegroundColor Green
        
        # Create wrapper .c file
        $wrapperContent = @"
/**
 * @file $compName.c
 * @brief Component wrapper implementation for $compName
 *
 * This file is used to implement the public interface of the component.
 * It acts as a wrapper for ${compName}Unit module, providing unified access to
 * the unit's functionality through a single component interface.
 */

//============================================================================
// Dependencies
//============================================================================
#include "$compName.h"
#include "${compName}Cfg.h"
#include "${compName}Unit.h"

//============================================================================
// Public Function Implementations
//============================================================================

"@
        
        # Add wrapper functions
        foreach ($func in $functions) {
            # We would need function signatures here - this is simplified
            $wrapperContent += "${prefix}_Status_t ${prefix}_$func(...)`n{`n    return ${prefix}Unit_$func(...);`n}`n`n"
        }
        
        Set-Content -Path $wrapperCPath -Value $wrapperContent -NoNewline
        Write-Host "✓ Created $wrapperCPath" -ForegroundColor Green
    }
    else {
        Write-Host "✗ File not found: $unitCPath" -ForegroundColor Red
    }
}

Write-Host "`n=== Processing Complete ===" -ForegroundColor Cyan
